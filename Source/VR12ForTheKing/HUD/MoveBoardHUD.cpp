// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/MoveBoardHUD.h"

#include "Net/UnrealNetwork.h"

#include "../Widget/StatusWidget.h"
#include "../Widget/MoveWidget.h"
#include "../Widget/TileEventWidget.h"

#include "../Component/MoveManagerComponent.h"
#include "../MyGameModeBase.h"

void AMoveBoardHUD::BeginPlay()
{
	if (bIsInit == false)
	{
		bIsInit = true;
		InitHUD();

		if (HasAuthority())
		{
			GetWorld()->GetAuthGameMode()->FindComponentByClass<UMoveManagerComponent>()->StartTurn();
		}
	}
}

void AMoveBoardHUD::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMoveBoardHUD, bIsInit);
}

void AMoveBoardHUD::InitHUD()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	check(PC);

	check(StatusWidgetClass != nullptr);
	StatusWidget = CreateWidget<UStatusWidget>(GetWorld()->GetFirstPlayerController(), StatusWidgetClass);
	check(StatusWidget != nullptr);
	StatusWidget->AddToViewport();

	check(MoveWidgetClass != nullptr);
	MoveWidget = CreateWidget<UMoveWidget>(GetWorld()->GetFirstPlayerController(), MoveWidgetClass);
	check(MoveWidget != nullptr);
	MoveWidget->AddToViewport();

	/*check(TileEventWidgetClass != nullptr);
	TileEventWidget = CreateWidget<UTileEventWidget>(GetWorld()->GetFirstPlayerController(), TileEventWidgetClass);
	check(TileEventWidget != nullptr);
	TileEventWidget->AddToViewport();*/
}

UStatusWidget* AMoveBoardHUD::GetStatusWidget() const
{
	return StatusWidget;
}

UMoveWidget* AMoveBoardHUD::GetMoveWidget() const
{
	return MoveWidget;
}

UTileEventWidget* AMoveBoardHUD::GetTileEventWidget() const
{
	return TileEventWidget;
}