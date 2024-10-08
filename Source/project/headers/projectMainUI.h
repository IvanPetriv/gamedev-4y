// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "projectMainUI.generated.h"

/**
 * 
 */
UCLASS()
class PROJECT_API UprojectMainUI : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

protected:
	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* Button_11;
	
	UFUNCTION()
	void OnClickedHandler();
};
