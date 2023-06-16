// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MainMenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"
#include "Components/Button.h"

void UMainMenuWidget::NativeConstruct()
{
	Btn_NewGame->OnClicked.AddDynamic(this, &UMainMenuWidget::NewGameButtonOnClicked);
	Btn_JoinGame->OnClicked.AddDynamic(this, &UMainMenuWidget::JoinGameButtonOnClicked);
	Btn_Quit->OnClicked.AddDynamic(this, &UMainMenuWidget::QuitButtonOnClicked);
}

void UMainMenuWidget::NewGameButtonOnClicked()
{
	GetWorld()->ServerTravel("/Game/Maps/L_SelectCharacter?listen");
}

void UMainMenuWidget::JoinGameButtonOnClicked()
{
	GetWorld()->GetFirstPlayerController()->ClientTravel("127.0.0.1", ETravelType::TRAVEL_Absolute, false);
}

void UMainMenuWidget::QuitButtonOnClicked()
{
	UWorld* World = GetWorld();
	APlayerController* PlayerController = World->GetFirstPlayerController();
	UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}