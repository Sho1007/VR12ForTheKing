// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "HexGrid/HexGridManager.h"
#include "HexGrid/HexTile.h"
#include "Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Character/MyPlayerController.h"
#include "AIController.h"
#include "Widget/MoveWidget.h"
#include "Event/TileEventManager.h"
#include "Event/TileEventMeshCapturor.h"
#include "Event/EnemyEventActor.h"
#include "Component/BattleManagerComponent.h"
#include "Component/MoveManagerComponent.h"
#include "Component/BattleComponent.h"
#include "Widget/TurnWidget.h"
#include "Widget/StatusWidget.h"
#include "Widget/InventoryWidget.h"

AMyGameModeBase::AMyGameModeBase()
{
	// BattleManager
	BattleManager = CreateDefaultSubobject<UBattleManagerComponent>(TEXT("BattleManager"));
	checkf(BattleManager != nullptr, TEXT("BattleManager is not spawned"));
	BattleManager->SetGameMode(this);

	// MoveManager
	MoveManager = CreateDefaultSubobject<UMoveManagerComponent>(TEXT("MoveManager"));
	check(MoveManager != nullptr);


	// HexGridManager
	HexGridManager = CreateDefaultSubobject<UHexGridManager>(TEXT("HexGridManager"));
	check(HexGridManager != nullptr);

	// TileEventManager
	TileEventManager = CreateDefaultSubobject<UTileEventManager>(TEXT("TileEventManager"));
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	MoveManager->Init();

	HexGridManager->CreateGrid();
	CreatePlayer();

	NextTile = NULL;

	MoveManager->StartTurn();

	CreateTurnWidget();
	CreateStatusWidget();
}

void AMyGameModeBase::LeftClick(APlayerController* PlayerController)
{
	if (!MoveManager->IsMoved() && MoveManager->GetCurrentController() == PlayerController)
	{
		MoveManager->MoveCharacter();
	}
}

void AMyGameModeBase::CheckFocusActor(AActor* NewActor, APlayerController* TargetPlayerController)
{
	if (NewActor == nullptr) return;
	CheckEndTile(NewActor, TargetPlayerController);
	CheckTileEvent(NewActor, TargetPlayerController);
}

void AMyGameModeBase::CheckEndTile(AActor* NewActor, APlayerController* TargetPlayerController)
{
	if (!MoveManager->IsMoved() && MoveManager->GetCurrentController() == TargetPlayerController)
	{
		AHexTile* HexTile = Cast<AHexTile>(NewActor);
		if (HexTile)
		{
			HexGridManager->SetEndTile(HexTile, MoveManager->GetMovableCount());
		}
	}
}

void AMyGameModeBase::CheckTileEvent(AActor* NewActor, APlayerController* TargetPlayerController)
{
	if (TargetPlayerController != GetWorld()->GetFirstPlayerController()) return;
	TileEventManager->SetFocusTarget(NewActor);
}

void AMyGameModeBase::SetEndTile(AHexTile* NewEndTile)
{
	HexGridManager->SetEndTile(NewEndTile, MoveManager->GetMovableCount());
}

void AMyGameModeBase::ReachToTile()
{
	MoveManager->ReachToDestination();
}

void AMyGameModeBase::FinishUpdateMoveWidget()
{
	MoveManager->GetMoveWidget()->HideMoveJudgeWidget();
}

void AMyGameModeBase::DoEventAction(ETileEventActionType NewEventActionType)
{
	switch (NewEventActionType)
	{
	case ETileEventActionType::Battle:
		TileEventManager->HideWidget();
		MoveManager->HideWidget();
		TurnWidget->ChangetoBattleTurnWidget();
		for (int i = 0; i < CharacterArray.Num(); ++i)
		{
			CharacterArray[i]->SetMoveMode(false);
		}
		BattleManager->InitBattle(MoveManager->GetNextTile());
		break;
	case ETileEventActionType::Retreat:
		break;
	}
}

UTurnWidget* AMyGameModeBase::GetTurnWidget() const
{
	return TurnWidget;
}

void AMyGameModeBase::CreatePlayer()
{
	check(CharacterClass != nullptr);

	FVector SpawnLocation = HexGridManager->GetTile(2,8)->GetActorLocation();
	SpawnLocation.Z += 100;
	for (int i = 0; i < 3; ++i)
	{
		AMyCharacter* MyCharacter = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, FRotator(0, 0, 0));
		MyCharacter->Init(this);
		MyCharacter->SetCurrentTile(HexGridManager->GetTile(2, 8));
		CharacterArray.Add(MyCharacter);
		//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Yellow, FString::Printf(TEXT("CharacterArray Num : %d"), CharacterArray.Num()));
		if (MyCharacter->GetCurrentTile() == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("AMyGameModeBase::CreatePlayer : CurrentTile is nullptr"));
		}
	}

	int32 PlayerNum = UGameplayStatics::GetNumPlayerControllers(this);
	for (int i = 0; i < PlayerNum; ++i)
	{
		PlayerControllerArray.Add(Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, i)));
	}
	int32 CurrentPos = 0;
	for (int i = 0; i < CharacterArray.Num(); ++i)
	{
		PlayerControllerArray[CurrentPos]->AddPlayerCharacter(CharacterArray[i]);
		CurrentPos = (CurrentPos + 1) % PlayerNum;
	}


	MoveManager->SetPlayerCharacterArray(CharacterArray);
	MoveManager->SetPlayerControllerArray(PlayerControllerArray);
}

void AMyGameModeBase::CreateTurnWidget()
{
	checkf(TurnWidgetClass != nullptr, TEXT("TurnWidgetClass is nullptr"));
	TurnWidget = CreateWidget<UTurnWidget>(GetWorld()->GetFirstPlayerController(), TurnWidgetClass);
	checkf(TurnWidget != nullptr, TEXT("TurnWidget is not created"));
	TurnWidget->AddToPlayerScreen(0);
	TurnWidget->InitWidget();
}

void AMyGameModeBase::CreateStatusWidget()
{
	checkf(StatusWidgetClass != nullptr, TEXT("StatusWidgetClass is nullptr"));
	StatusWidget = CreateWidget<UStatusWidget>(GetWorld()->GetFirstPlayerController(), StatusWidgetClass);
	checkf(StatusWidget != nullptr, TEXT("StatusWidget is not created"));
	StatusWidget->AddToPlayerScreen(0);
	StatusWidget->SetParentToChild();
	StatusWidget->SetOwnerCharacter(CharacterArray);
	StatusWidget->HideWidget();

	// Todo : Create InitWidget Function
	//StatusWidget->InitWidget();
}

void AMyGameModeBase::CreateInventoryWidget()
{
	checkf(InventoryWidgetClass != nullptr, TEXT("InventoryWidgetClass is not valid"));
	InventoryWidget = CreateWidget<UInventoryWidget>(GetWorld()->GetFirstPlayerController(), InventoryWidgetClass);
	checkf(InventoryWidget != nullptr, TEXT("InventoryWidget is not created"));
	InventoryWidget->AddToPlayerScreen(0);
	//InventoryWidget->HideWidget();
}

UTileEventManager* AMyGameModeBase::GetTileEventManager()
{
	return TileEventManager;
}