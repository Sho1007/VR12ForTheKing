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
}

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	// TileEventManager
	checkf(TileEventManagerClass != nullptr, TEXT("AMyGameModeBase::BeginPlay : Tile Event Manager Class is nullptr"));
	TileEventManager = GetWorld()->SpawnActor<ATileEventManager>(TileEventManagerClass, FVector(0, 0, 0), FRotator(0,0,0));
	checkf(TileEventManager != nullptr, TEXT("AMyGameModeBase::BeginPlay : Tile Event Manager is not spawned"));

	MoveManager->Init();

	// TileEventMeshCapturor
	checkf(TileEventMeshCapturorClass != nullptr, TEXT("AMyGameModeBase::BeginPlay : TileEventMeshCapturor Class is nullptr"));
	TileEventMeshCapturor = GetWorld()->SpawnActor<ATileEventMeshCapturor>(TileEventMeshCapturorClass, FVector(0, 0, 0), FRotator(0, 0, 0));
	checkf(TileEventMeshCapturor != nullptr, TEXT("AMyGameModeBase::BeginPlay : TileEventMeshCapturor is not spawned"));

	HexGridManager->CreateGrid();
	CreatePlayer();

	NextTile = NULL;

	MoveManager->StartTurn();
}

void AMyGameModeBase::LeftClick(APlayerController* PlayerController)
{
	if (!MoveManager->IsMoved() && MoveManager->GetCurrentController() == PlayerController)
	{
		UE_LOG(LogTemp, Warning, TEXT("AMyGameModeBase::LeftClick : Called"));
	}
}

void AMyGameModeBase::SetEndTile(AHexTile* NewEndTile)
{
	HexGridManager->SetEndTile(NewEndTile, MoveManager->GetMovableCount());
}

void AMyGameModeBase::MoveCharacter()
{
	bIsMoved = true;
	//GEngine->AddOnScreenDebugMessage(-1, 60.0f, FColor::Yellow, FString::Printf(TEXT("MoveCharacter Called")));
	NextTile = HexGridManager->GetNextPath();
	if (NextTile)
	{
		//UE_LOG(LogTemp, Error, TEXT("NextTile : %s"), *NextTile->GetPos().ToString());
		CurrentTileEvent = NextTile->GetTileEvent();
		if (CurrentTileEvent == nullptr)
		{
			CurrentCharacter->SetDestination(NextTile->GetActorLocation());
		}
		else
		{
			// Todo : Move Half Distance to Event Tile
			MoveWidget->InitEventWidget(CurrentTileEvent);
			TileEventMeshCapturor->SetFocusTarget(CurrentTileEvent);
			MoveWidget->ShowEventWidget();
		}
	}
	else
	{
		//UE_LOG(LogTemp, Error, TEXT("NextTile is NULL"));
		// NextTile == NULL 목적지에 도착함
		if (CurrentMovableCount)
		{
			HexGridManager->SetStartTile(CurrentCharacter->GetCurrentTile());
			bIsMoved = false;
		}
		else
		{
			EndTurn();
		}
	}
	
}

void AMyGameModeBase::ReachToTile()
{
	//UE_LOG(LogTemp, Error, TEXT("ReachToTile is Called"));

	if (CurrentCharacter->GetCurrentTile() != NextTile)
	{
		CurrentMovableCount--;
	}
	
	//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Cyan, FString::Printf(TEXT("CurrentMovalbeCount : %d"), CurrentMovableCount));

	if (NextTile)
	{
		//UE_LOG(LogTemp, Error, TEXT("NextTile : %s"), *NextTile->GetPos().ToString());
		NextTile->SetIsPath(false);
		CurrentCharacter->SetCurrentTile(NextTile);
	}
	else
	{
		//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Red, FString::Printf(TEXT("NextTile is NULL")));
	}
	
	// Todo : Random Encounter
	MoveCharacter();
}

const APlayerController* AMyGameModeBase::GetCurrentPlayer() const
{
	return CurrentPlayer;
}

const bool AMyGameModeBase::GetIsMoved() const
{
	return bIsMoved;
}

void AMyGameModeBase::FinishUpdateMoveWidget()
{
	bIsMoved = false;
}

void AMyGameModeBase::HideEventInfoWidget()
{
	MoveWidget->HideEventInfoWidget();
}

void AMyGameModeBase::InitAndShowEventInfoWidget(AEventActor* NewEventActor, FVector2D WidgetPos)
{
	MoveWidget->InitEventInfoWidget(NewEventActor);
	MoveWidget->ShowEventInfoWidget(WidgetPos);
}

ATileEventManager* AMyGameModeBase::GetTileEventManager()
{
	return TileEventManager;
}

void AMyGameModeBase::DoEventAction(ETileEventActionType NewEventActionType)
{
	switch (NewEventActionType)
	{
	case ETileEventActionType::Battle:
		MoveWidget->HideEventWidget();
		BattleManager->InitBattle(NextTile);
		break;
	case ETileEventActionType::Retreat:
		break;
	}
}

void AMyGameModeBase::CreatePlayer()
{
	if (CharacterClass)
	{
		FVector SpawnLocation(0, 0, 100);
		for (int i = 0; i < 3; ++i)
		{
			AMyCharacter* MyCharacter = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, FRotator(0, 0, 0));
			MyCharacter->Init(this);
			MyCharacter->SetCurrentTile(HexGridManager->GetTile(0,0));
			CharacterArray.Add(MyCharacter);
			//GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Yellow, FString::Printf(TEXT("CharacterArray Num : %d"), CharacterArray.Num()));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase:: CharacterClass is not valid"));
	}
	int32 PlayerNum = UGameplayStatics::GetNumPlayerControllers(this);
	for (int i = 0; i < PlayerNum; ++i)
	{
		PlayerControllerArray.Add(Cast<AMyPlayerController>(UGameplayStatics::GetPlayerController(this, i)));
	}

	MoveManager->SetPlayerCharacterArray(CharacterArray);
	MoveManager->SetPlayerControllerArray(PlayerControllerArray);
}

void AMyGameModeBase::EndTurn()
{
	//Todo: Heal as much as Remain Movable Count;
	//CurrentCharacter->HealHP(CurrentMovableCount);
	DoNextTurn();
}

void AMyGameModeBase::DoNextTurn()
{
	if (CharacterArray.Num() == 0)
	{
		UE_LOG(LogTemp, Error, TEXT("Character Array is Empty"));
		return;
	}

	CurrentTurn++;
	CurrentCharacter = CharacterArray[(CurrentTurn - 1) % CharacterArray.Num()];
	CurrentPlayer = PlayerControllerArray[(CurrentTurn - 1) % PlayerControllerArray.Num()];

	// Spawn Event
	SpawnEvent();

	//UE_LOG(LogTemp, Warning, TEXT("CurrentCharacter : %s , CurrentPlayerController : %s"), *CurrentCharacter->GetName(), *CurrentPlayer->GetName());
	// 카메라 이동
	// // 시작 바닥 설정

	HexGridManager->SetStartTile(CurrentCharacter->GetCurrentTile());
}

void AMyGameModeBase::SpawnEvent()
{
	if (CurrentCharacter == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("AMyGameModeBase::SpawnEvent : CurrentCharacter is NULL"));
		return;
	}
	else
	{
		if (CurrentCharacter->GetCurrentTile() == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("AMyGameModeBase::SpawnEvent : CurrentTile is NULL"));
			return;
		}
	}

	NeighborTileArray.Empty();

	HexGridManager->FindNeighborTiles(NeighborTileArray, CurrentCharacter->GetCurrentTile(), 2);

	for (AHexTile* Iter : NeighborTileArray)
	{
		if (Iter->GetIsSearched() || Iter->GetTileEvent() != nullptr || Iter->GetInTileCharacterArray().Num() > 0) continue;

		if (FMath::RandRange(0.0, 1.0) <= TileEventManager->GetEventOccurChance())
		{
			Iter->Search();
			Iter->SpawnEvent();
		}
	}
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