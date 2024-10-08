// Fill out your copyright notice in the Description page of Project Settings.


#include "projectEnemySpawnManager.h"

// Sets default values
AprojectEnemySpawnManager::AprojectEnemySpawnManager()
{
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AprojectEnemySpawnManager::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundTargetPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AprojectEnemySpawn::StaticClass(), FoundTargetPoints);
	UE_LOG(LogTemp, Warning, TEXT("Found %d Target Points"), FoundTargetPoints.Num());

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	for (AActor* FoundTargetPoint : FoundTargetPoints)
	{
		AprojectEnemy* SpawnedEnemy = GetWorld()->SpawnActor<AprojectEnemy>(BaseEnemyBP, FoundTargetPoint->GetActorTransform(), SpawnParams);
		if (SpawnedEnemy)
		{
			UE_LOG(LogTemp, Warning, TEXT("Enemy spawned successfully."));
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Failed to spawn enemy."));
		}
	}
}


