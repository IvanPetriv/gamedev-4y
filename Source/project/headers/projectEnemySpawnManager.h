// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "projectEnemy.h"
#include "projectEnemySpawn.h"

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Actor.h"
#include "projectEnemySpawnManager.generated.h"

UCLASS()
class PROJECT_API AprojectEnemySpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AprojectEnemySpawnManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	UPROPERTY(EditAnywhere)
	TSubclassOf<AprojectEnemy> BaseEnemyBP;
};
