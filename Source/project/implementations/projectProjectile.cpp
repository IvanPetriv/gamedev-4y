// Copyright Epic Games, Inc. All Rights Reserved.

#include "projectProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

AprojectProjectile::AprojectProjectile() 
{
	PrimaryActorTick.bCanEverTick = true;

	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(5.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &AprojectProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 900.f;
	ProjectileMovement->MaxSpeed = 9000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Bounciness = 0.8f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	InitialLifeSpan = 3.0f;
}

void AprojectProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//FVector CurrentVelocity = ProjectileMovement->Velocity;

	//float Time = GetWorld()->GetTimeSeconds();
	//float CircleAmplitude = 150.0f;
	//float CircleFrequency = 2.0f;  
	//float WaveAmplitude = 100.0f;  
	//float WaveFrequency = 3.0f;    

	//CurrentVelocity.Y = CircleAmplitude * FMath::Sin(CircleFrequency * Time);
	//CurrentVelocity.Z = WaveAmplitude * FMath::Sin(WaveFrequency * Time);

	//ProjectileMovement->Velocity = CurrentVelocity;
}

void AprojectProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		Destroy();
	}
}