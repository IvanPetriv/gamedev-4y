// Copyright Epic Games, Inc. All Rights Reserved.

#include "projectCharacter.h"
#include "projectProjectile.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/InputSettings.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogFPChar, Warning, All);


AprojectCharacter::AprojectCharacter()
{
    // Set size for collision capsule
    GetCapsuleComponent()->InitCapsuleSize(55.f, 96.0f);

    // Create a CameraComponent    
    FirstPersonCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
    FirstPersonCameraComponent->SetupAttachment(GetCapsuleComponent());
    FirstPersonCameraComponent->SetRelativeLocation(FVector(-39.56f, 1.75f, 64.f)); // Position the camera
    FirstPersonCameraComponent->bUsePawnControlRotation = true;

    // Create a gun mesh component
    FP_Gun = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_Gun"));
    FP_Gun->SetOnlyOwnerSee(false);
    FP_Gun->bCastDynamicShadow = false;
    FP_Gun->CastShadow = false;
    FP_Gun->SetupAttachment(this->GetMesh(), TEXT("LeftHandSocket")); // Attach gun to the character's mesh

    FP_MuzzleLocation = CreateDefaultSubobject<USceneComponent>(TEXT("MuzzleLocation"));
    FP_MuzzleLocation->SetupAttachment(FP_Gun);
    FP_MuzzleLocation->SetRelativeLocation(FVector(0.2f, 45.4f, -10.6f));

    // Default offset from the character location for projectiles to spawn
    GunOffset = FVector(100.0f, 0.0f, 10.0f);
}

void AprojectCharacter::BeginPlay()
{
    // Call the base class  
    Super::BeginPlay();

    // Attach gun mesh component to Skeleton, doing it here because the skeleton is not yet created in the constructor
    FP_Gun->AttachToComponent(this->GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), TEXT("LeftHandSocket"));
}

//////////////////////////////////////////////////////////////////////////
// Input

void AprojectCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
    // set up gameplay key bindings
    check(PlayerInputComponent);

    // Bind jump events
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
    PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

    // Bind fire event
    PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &AprojectCharacter::OnFire);

    // Bind movement events
    PlayerInputComponent->BindAxis("MoveForward", this, &AprojectCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AprojectCharacter::MoveRight);

    // "turn" handles devices that provide an absolute delta, such as a mouse.
    PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
    PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
}

void AprojectCharacter::OnFire()
{
    // try and fire a projectile
    if (ProjectileClass != nullptr)
    {
        UWorld* const World = GetWorld();
        if (World != nullptr)
        {
            const FRotator SpawnRotation = GetControlRotation();
            // MuzzleOffset is in camera space, so transform it to world space before offsetting from the character location to find the final muzzle position
            const FVector SpawnLocation = ((FP_MuzzleLocation != nullptr) ? FP_MuzzleLocation->GetComponentLocation() : GetActorLocation()) + SpawnRotation.RotateVector(GunOffset);

            // Set Spawn Collision Handling Override
            FActorSpawnParameters ActorSpawnParams;
            ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;

            // spawn the projectile at the muzzle
            World->SpawnActor<AprojectProjectile>(ProjectileClass, SpawnLocation, SpawnRotation, ActorSpawnParams);
        }
    }

    // try and play the sound if specified
    if (FireSound != nullptr)
    {
        UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
    }

    // try and play a firing animation if specified
    if (FireAnimation != nullptr)
    {
        // Get the animation object for the arms mesh
        UAnimInstance* AnimInstance = this->GetMesh()->GetAnimInstance();
        if (AnimInstance != nullptr)
        {
            AnimInstance->Montage_Play(FireAnimation, 1.f);
        }
    }
}

void AprojectCharacter::MoveForward(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorForwardVector(), Value);
    }
}

void AprojectCharacter::MoveRight(float Value)
{
    if (Value != 0.0f)
    {
        // add movement in that direction
        AddMovementInput(GetActorRightVector(), Value);
    }
}
