// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/MoveManagerComponent.h"

#include "../HUD/MoveBoardHUD.h"
#include "../Widget/MoveWidget.h"
#include "Kismet/KismetMathLibrary.h"
#include "../MyGameModeBase.h"	// 추후 Component 통신 되면 지워야할수도
#include "../HexGrid/HexGridManager.h"
#include "../HexGrid/HexTile.h"
#include "../Event/TileEventManager.h"
#include "../Character/MyCharacter.h"

// Sets default values for this component's properties
UMoveManagerComponent::UMoveManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	MoveJudgeArray.Init(true, 5);
}


// Called when the game starts
void UMoveManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
	Init();

	HexGridManager = Cast<UHexGridManager>(GetOwner()->GetComponentByClass(UHexGridManager::StaticClass()));
	check(HexGridManager != nullptr);
}

void UMoveManagerComponent::Init()
{
	// Todo : Load DataFile

	Day = 0;
	Turn = 0;
}

void UMoveManagerComponent::PrepareTurn()
{
	check(PlayerCharacterArray.Num() > 0);

	// Todo : Update Turn Widget;
	Turn++;
	if (Turn / 15 > Day)
	{
		Day++;
	}
	CurrentCharacter = PlayerCharacterArray[(Turn - 1) % PlayerCharacterArray.Num()];
	CurrentController = PlayerControllerArray[(Turn - 1) % PlayerControllerArray.Num()];

	ExecuteTurn();
}

void UMoveManagerComponent::ExecuteTurn()
{
	// SpawnEvent
	UActorComponent*  ActorComponent = GetOwner()->GetComponentByClass(UTileEventManager::StaticClass());
	check(ActorComponent != nullptr);
	UTileEventManager* TileEventManager = Cast<UTileEventManager>(ActorComponent);
	check(TileEventManager != nullptr);
	TileEventManager->SpawnEvent(CurrentCharacter->GetCurrentTile());

	CheckMoveCount();
	//GetWorld()->GetFirstPlayerController()->GetHUD<AMoveBoardHUD>()->GetMoveWidget()->UpdateMoveJudge(MoveJudgeArray);

	HexGridManager->SetStartTile(CurrentCharacter->GetCurrentTile());
	bIsMoved = false;
}

void UMoveManagerComponent::FinishTurn()
{
	PrepareTurn();
}

void UMoveManagerComponent::CheckMoveCount()
{
	MovableCount = 2;
	for (int i = 2; i < 5; ++i)
	{
		MoveJudgeArray[i] = UKismetMathLibrary::RandomBoolWithWeight(0.5f);
		if (MoveJudgeArray[i])
		{
			MovableCount++;
		}
	}
}

void UMoveManagerComponent::MoveCharacter()
{
	GetWorld()->GetFirstPlayerController()->GetHUD<AMoveBoardHUD>()->GetMoveWidget()->HideMoveJudgeWidget();

	bIsMoved = true;

	// 현재는 HexGridManager 가 Component가 아니라서 하드코딩 -> 추후 컴포넌트로 바꾸고 컴포넌트끼리 통신하도록
	NextTile = HexGridManager->GetNextPath();

	UActorComponent* ActorComponent = GetOwner()->GetComponentByClass(UTileEventManager::StaticClass());
	check(ActorComponent != nullptr);
	UTileEventManager* TEM = Cast<UTileEventManager>(ActorComponent);
	if (NextTile)
	{
		if (TEM->SetCurrentTileEvent(NextTile))
		{
			// Todo : Move Half Distance to Event Tile;
		}
		else
		{
			CurrentCharacter->SetDestination(NextTile->GetActorLocation());
		}
	}
	else
	{
		if (MovableCount)
		{
			HexGridManager->SetStartTile(CurrentCharacter->GetCurrentTile());
			bIsMoved = false;
		}
		else
		{
			FinishTurn();
		}
	}
}

void UMoveManagerComponent::ReachToDestination()
{
	if (CurrentCharacter->GetCurrentTile() != NextTile)
	{
		MovableCount--;
	}

	if (NextTile)
	{
		NextTile->SetIsPath(false);
		CurrentCharacter->SetCurrentTile(NextTile);
	}

	MoveCharacter();
}

AHexTile* UMoveManagerComponent::GetNextTile() const
{
	return NextTile;
}

int32 UMoveManagerComponent::GetMovableCount() const
{
	return MovableCount;
}

void UMoveManagerComponent::StartTurn()
{
	PrepareTurn();
}

const bool UMoveManagerComponent::IsMoved() const
{
	return bIsMoved;
}

const AMyPlayerController* UMoveManagerComponent::GetCurrentController() const
{
	return CurrentController;
}

void UMoveManagerComponent::SetPlayerCharacterArray(const TArray<AMyCharacter*>& NewPlayerCharacterArray)
{
	PlayerCharacterArray = NewPlayerCharacterArray;
}

void UMoveManagerComponent::SetPlayerControllerArray(const TArray<AMyPlayerController*>& NewPlayerControllerArray)
{
	PlayerControllerArray = NewPlayerControllerArray;
}