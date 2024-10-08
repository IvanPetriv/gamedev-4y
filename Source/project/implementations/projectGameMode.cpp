// Copyright Epic Games, Inc. All Rights Reserved.

#include "projectGameMode.h"
#include "projectHUD.h"
#include "projectCharacter.h"
#include "UObject/ConstructorHelpers.h"

AprojectGameMode::AprojectGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AprojectHUD::StaticClass();
}
