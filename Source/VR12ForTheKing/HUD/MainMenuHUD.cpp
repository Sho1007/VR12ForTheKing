// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/MainMenuHUD.h"

#include "Net/UnrealNetwork.h"

#include "../Widget/MainMenuWidget.h"

AMainMenuHUD::AMainMenuHUD(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bReplicates = true;
	bIsInit = false;
}

void AMainMenuHUD::BeginPlay()
{
	if (bIsInit == false)
	{
		bIsInit = true;
		InitHUD();
	}
}

void AMainMenuHUD::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainMenuHUD, bIsInit);
}

void AMainMenuHUD::InitHUD()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	check(MainMenuWidgetClass != nullptr);
	MainMenuWidget = CreateWidget<UMainMenuWidget>(PC, MainMenuWidgetClass, FName(TEXT("MainMenuWidget")));
	check(MainMenuWidget != nullptr);
	MainMenuWidget->AddToViewport();

	PC->SetShowMouseCursor(true);
	FInputModeUIOnly InputMode;
	PC->SetInputMode(InputMode);
}