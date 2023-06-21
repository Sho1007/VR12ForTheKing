// Fill out your copyright notice in the Description page of Project Settings.


#include "../HUD/MoveBoardHUD.h"

#include "Net/UnrealNetwork.h"

#include "../Widget/StatusWidget.h"
#include "../Widget/MoveWidget.h"
#include "../Widget/TileEventWidget.h"
#include "../Widget/BattleWidget.h"
#include "../Widget/TurnWidget.h"
#include "../Widget/BattleTurnWidget.h"

#include "../PlayerController/MoveBoardPlayerController.h"

void AMoveBoardHUD::BeginPlay()
{
	if (bIsInit == false)
	{
		bIsInit = true;
		InitHUD();
	}
}

void AMoveBoardHUD::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMoveBoardHUD, bIsInit);
}

void AMoveBoardHUD::InitHUD()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("AMoveBoardHUD::InitHUD")));
	AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(GetOwningPlayerController());
	check(PC);

	// Create StatusWidget
	check(StatusWidgetClass != nullptr);
	StatusWidget = CreateWidget<UStatusWidget>(GetWorld()->GetFirstPlayerController(), StatusWidgetClass);
	check(StatusWidget != nullptr);
	StatusWidget->AddToViewport();
	// Create MoveWidget
	check(MoveWidgetClass != nullptr);
	MoveWidget = CreateWidget<UMoveWidget>(GetWorld()->GetFirstPlayerController(), MoveWidgetClass);
	check(MoveWidget != nullptr);
	MoveWidget->AddToViewport();
	// Create TileEventWidget
	check(TileEventWidgetClass != nullptr);
	TileEventWidget = CreateWidget<UTileEventWidget>(GetWorld()->GetFirstPlayerController(), TileEventWidgetClass);
	check(TileEventWidget != nullptr);
	TileEventWidget->AddToViewport();
	TileEventWidget->HideWidget();
	// Create BattleWidget
	check(BattleWidgetClass);
	BattleWidget = CreateWidget<UBattleWidget>(GetWorld()->GetFirstPlayerController(), BattleWidgetClass);
	check(BattleWidget);
	BattleWidget->AddToViewport();
	BattleWidget->HideWidget();
	// Create TurnWidget
	checkf(TurnWidgetClass != nullptr, TEXT("TurnWidgetClass is nullptr"));
	TurnWidget = CreateWidget<UTurnWidget>(GetWorld()->GetFirstPlayerController(), TurnWidgetClass);
	checkf(TurnWidget != nullptr, TEXT("TurnWidget is not created"));
	TurnWidget->AddToPlayerScreen(0);
	TurnWidget->InitWidget();
	// Set InputMode
	FInputModeGameAndUI InputMode;
	PC->SetInputMode(InputMode);
	PC->SetShowMouseCursor(true);
	PC->ReadyToPlay();
}

void AMoveBoardHUD::ChangeToBattleWidget()
{
	TileEventWidget->HideWidget();
	MoveWidget->HideWidget();
	TurnWidget->ChangetoBattleTurnWidget();
}

void AMoveBoardHUD::InitTileEventWidget(AEventActor* NewTileEvent)
{
	TileEventWidget->InitEventWidget(NewTileEvent);
}

void AMoveBoardHUD::SetBattleTurnArray(TArray<AMyCharacter*>& NewBattleTrunAray)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardHUD::SetBattleTurnArray")));
}

void AMoveBoardHUD::StartUpdateChanceSlot(int32 CoinSize, EStatusType StatusType, const TArray<bool>& NewChanceArray)
{
	BattleWidget->StartUpdateChanceSlot(CoinSize, StatusType, NewChanceArray);
}

void AMoveBoardHUD::InitBattleWidget(AMyCharacter* TargetCharacter)
{
	BattleWidget->InitWidget(TargetCharacter);
}

void AMoveBoardHUD::HideBattleWidget()
{
	BattleWidget->HideWidget();
}

void AMoveBoardHUD::ChangeToVictoryWidget()
{
	BattleWidget->ChangeToVictoryWidget();
}

void AMoveBoardHUD::DeleteHeartCount()
{
	TurnWidget->DeleteHeartCount();
}

void AMoveBoardHUD::AddUnitToImageArray(const TArray<AMyCharacter*>& NewImageArray)
{
	TurnWidget->GetBattleTurnWidget()->AddUnitToImageArray(NewImageArray);
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