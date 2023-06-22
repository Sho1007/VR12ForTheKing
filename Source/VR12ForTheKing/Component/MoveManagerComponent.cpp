// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/MoveManagerComponent.h"

#include "Net/UnrealNetwork.h"

#include "../HUD/MoveBoardHUD.h"
#include "../Widget/MoveWidget.h"
#include "Kismet/KismetMathLibrary.h"
//#include "../MyGameModeBase.h"	// 추후 Component 통신 되면 지워야할수도
#include "../HexGrid/HexGridManager.h"
#include "../HexGrid/HexTile.h"
#include "../Event/TileEventManager.h"
#include "../Character/MyCharacter.h"

#include "../GameState/MoveBoardGameState.h"

// Sets default values for this component's properties
UMoveManagerComponent::UMoveManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...

	MoveJudgeArray.Init(true, 5);

	SetIsReplicated(true);
}


// Called when the game starts
void UMoveManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

	HexGridManager = Cast<UHexGridManager>(GetOwner()->GetComponentByClass(UHexGridManager::StaticClass()));
	check(HexGridManager != nullptr);
}

void UMoveManagerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMoveManagerComponent, MovableCount);
	DOREPLIFETIME(UMoveManagerComponent, MoveJudgeArray);
}

void UMoveManagerComponent::Init(const TArray<AMyCharacter*>& NewPlayerCharacterArray)
{

	// Todo : Load DataFile

	Day = 0;
	Turn = 0;

	PlayerCharacterArray = NewPlayerCharacterArray;
}

void UMoveManagerComponent::TestMulticast_Implementation()
{
	GetWorld()->GetFirstPlayerController()->GetHUD<AMoveBoardHUD>()->GetMoveWidget()->UpdateMoveJudge(MoveJudgeArray);
}

void UMoveManagerComponent::HideMoveJudgeWidget_Implementation()
{
	GetWorld()->GetFirstPlayerController()->GetHUD<AMoveBoardHUD>()->GetMoveWidget()->HideMoveJudgeWidget();
}

void UMoveManagerComponent::PrepareTurn()
{
	// Todo : Update Turn Widget;
	CurrentTurnIndex++;
	if (Turn / 15 > Day)
	{
		Day++;
	}
	CurrentTurnCharacter = PlayerCharacterArray[CurrentTurnIndex % PlayerCharacterArray.Num()];

	ExecuteTurn();
}

void UMoveManagerComponent::ExecuteTurn()
{
	check(CurrentTurnCharacter != nullptr);
	// SpawnEvent
	UActorComponent*  ActorComponent = GetOwner()->GetComponentByClass(UTileEventManager::StaticClass());
	check(ActorComponent != nullptr);
	UTileEventManager* TileEventManager = Cast<UTileEventManager>(ActorComponent);
	check(TileEventManager != nullptr);
	TileEventManager->SpawnEvent(CurrentTurnCharacter->GetCurrentTile());

	CheckMoveCount();
	OnRep_MoveJudgeArray();

	HexGridManager->SetStartTile(CurrentTurnCharacter->GetCurrentTile());
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

void UMoveManagerComponent::OnRep_MoveJudgeArray()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("UMoveManagerComponent::OnRepMoveJudgeArray : MoveableCount : %d, MoveJudgeArray : %d %d %d %d %d"), MovableCount, MoveJudgeArray[0], MoveJudgeArray[1], MoveJudgeArray[2], MoveJudgeArray[3], MoveJudgeArray[4]));
	TestMulticast();
}

void UMoveManagerComponent::MoveCharacter()
{
	check(CurrentTurnCharacter != nullptr);

	bIsMoved = true;

	// 현재는 HexGridManager 가 Component가 아니라서 하드코딩 -> 추후 컴포넌트로 바꾸고 컴포넌트끼리 통신하도록
	NextTile = HexGridManager->GetNextPath();

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("UMoveManagerComponent::MoveCharacter : CurrentCharacter : %s, NextTile : %s"), *CurrentTurnCharacter->GetName(), *NextTile->GetName()));

	UTileEventManager* TileEventManager = GetOwner()->FindComponentByClass<UTileEventManager>();
	check(TileEventManager != nullptr);
	if (NextTile)
	{
		if (TileEventManager->SetCurrentTileEvent(NextTile))
		{
			// Todo : Move Half Distance to Event Tile;
		}
		else
		{
			CurrentTurnCharacter->SetDestination(NextTile->GetActorLocation(), 500, 30);
		}
	}
	else
	{
		if (MovableCount)
		{
			HexGridManager->SetStartTile(CurrentTurnCharacter->GetCurrentTile());
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
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("UMoveManagerComponent::ReachToDestination")));
	check(CurrentTurnCharacter != nullptr);

	if (CurrentTurnCharacter->GetCurrentTile() != NextTile)
	{
		MovableCount--;
	}

	if (NextTile)
	{
		NextTile->SetIsPath(false);
		CurrentTurnCharacter->SetCurrentTile(NextTile);
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

AMyCharacter* UMoveManagerComponent::GetCurrentTurnCharacter() const
{
	return CurrentTurnCharacter;
}

void UMoveManagerComponent::SetNextTurn()
{
}
