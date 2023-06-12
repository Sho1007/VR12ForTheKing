// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MainMenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Btn_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitButtonOnClicked);
}

void UMainMenuWidget::QuitButtonOnClicked()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}
