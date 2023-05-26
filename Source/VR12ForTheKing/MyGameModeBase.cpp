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
		BattleManager->InitBattle(MoveManager->GetNextTile());
		break;
	case ETileEventActionType::Retreat:
		break;
	}
}

void AMyGameModeBase::CreatePlayer()
{
	check(CharacterClass != nullptr);

	FVector SpawnLocation(0, 0, 100);
	for (int i = 0; i < 3; ++i)
	{
		AMyCharacter* MyCharacter = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, FRotator(0, 0, 0));
		MyCharacter->Init(this);
		MyCharacter->SetCurrentTile(HexGridManager->GetTile(0, 0));
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

	MoveManager->SetPlayerCharacterArray(CharacterArray);
	MoveManager->SetPlayerControllerArray(PlayerControllerArray);
}

void AMyGameModeBase::CalculateTurn()
{
	BattleTurnArray.Empty();
	UseBattleTurnArray.Empty();


	for (int32 i = 0; i < CharacterArray.Num(); ++i)
	{
		int32 CurrentTurnSpeed = CharacterArray[i]->GetTurnSpeed(CurrentBattleRound);

		bool bFindPos = false;
		for (int32 j = 0; j < BattleTurnArray.Num(); ++j)
		{
			if (BattleTurnArray[j]->GetTurnSpeed(CurrentBattleRound) >= CurrentTurnSpeed)
			{
				bFindPos = true;
				BattleTurnArray.Insert(CharacterArray[i], j);
				break;
			}
		}
		if (!bFindPos)
		{
			BattleTurnArray.Add(CharacterArray[i]);
		}
	}

	for (int32 i = 0; i < EnemyArray.Num(); ++i)
	{

		int32 CurrentTurnSpeed = EnemyArray[i]->GetTurnSpeed(CurrentBattleRound);

		bool bFindPos = false;
		for (int32 j = 0; j < BattleTurnArray.Num(); ++j)
		{
			if (BattleTurnArray[j]->GetTurnSpeed(CurrentBattleRound) >= CurrentTurnSpeed)
			{
				bFindPos = true;
				BattleTurnArray.Insert(EnemyArray[i], j);
				break;
			}
		}
		if (!bFindPos)
		{
			BattleTurnArray.Add(EnemyArray[i]);
		}
	}

	//BattleWidget->SetTurnArray(BattleTurnArray);

	// Make Use Array
	for (int i = 0; i < BattleTurnArray.Num() * 2; ++i)
	{
		UseBattleTurnArray.Add(BattleTurnArray[i % BattleTurnArray.Num()]);
	}
}

UTileEventManager* AMyGameModeBase::GetTileEventManager()
{
	return TileEventManager;
}