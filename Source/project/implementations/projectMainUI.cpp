// Fill out your copyright notice in the Description page of Project Settings.


#include "projectMainUI.h"

void UprojectMainUI::NativeConstruct() {
	Super::NativeConstruct();
	ensure(Button_11);

	Button_11->OnClicked.AddUniqueDynamic(this, &UprojectMainUI::OnClickedHandler);
}

void UprojectMainUI::OnClickedHandler() {
	UE_LOG(LogTemp, Log, TEXT("Button clicked"));
}