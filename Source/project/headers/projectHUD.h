// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once 

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "projectHUD.generated.h"

UCLASS()
class AprojectHUD : public AHUD
{
	GENERATED_BODY()

public:
	AprojectHUD();

	virtual void DrawHUD() override;

private:
	class UTexture2D* CrosshairTex;

};

