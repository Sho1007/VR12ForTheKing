// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/MoveManagerComponent.h"

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
	GetWorld()->GetTimerManager().SetTimer(SetTileEventManagerHandle, this, &UMoveManagerComponent::SetTileEventManager, 0.1f, true);
}

void UMoveManagerComponent::Init()
{
	// Todo : Load DataFile

	Day = 0;
	Turn = 0;

	CreateMoveWidget();
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
	CurrentCharacter = PlayerCharacterArray[(Turn)-1 % PlayerCharacterArray.Num()];
	CurrentController = PlayerControllerArray[(Turn - 1) % PlayerControllerArray.Num()];

	ExecuteTurn();
}

void UMoveManagerComponent::ExecuteTurn()
{
	// SpawnEvent

	CheckMoveCount();
	MoveWidget->UpdateMoveJudge(MoveJudgeArray);

	HexGridManager->SetStartTile(CurrentCharacter->GetCurrentTile());
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
	bIsMoved = true;

	// 현재는 HexGridManager 가 Component가 아니라서 하드코딩 -> 추후 컴포넌트로 바꾸고 컴포넌트끼리 통신하도록
	AHexTile* NextTile = HexGridManager->GetNextPath();
	if (NextTile)
	{
		if (TileEventManager->SetTileEvent(NextTile))
		{
			// Todo : Move Half Distance to Event Tile;
			MoveWidget->InitEventWidget(TileEventManager->GetTileEvent());
			MoveWidget->ShowEventWidget();
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

void UMoveManagerComponent::CreateMoveWidget()
{
	check(MoveWidgetClass != nullptr && GEngine != nullptr);
	MoveWidget = CreateWidget<UMoveWidget>(GEngine->GetFirstLocalPlayerController(GetWorld()), MoveWidgetClass);
	check(MoveWidget != nullptr);
	MoveWidget->AddToPlayerScreen(0);
	MoveWidget->HideEventInfoWidget();
	MoveWidget->HideEventWidget();
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

const APlayerController* UMoveManagerComponent::GetCurrentController() const
{
	return CurrentController;
}

const UMoveWidget* UMoveManagerComponent::GetMoveWidget() const
{
	return MoveWidget;
}

void UMoveManagerComponent::SetPlayerCharacterArray(const TArray<AMyCharacter*>& NewPlayerCharacterArray)
{
	PlayerCharacterArray = NewPlayerCharacterArray;
}

void UMoveManagerComponent::SetPlayerControllerArray(const TArray<APlayerController*>& NewPlayerControllerArray)
{
	PlayerControllerArray = NewPlayerControllerArray;
}

void UMoveManagerComponent::SetTileEventManager()
{
	AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(GetOwner());
	if (GameMode != nullptr)
	{
		ATileEventManager* NewTileEventManager = GameMode->GetTileEventManager();
		if (NewTileEventManager != nullptr)
		{
			GetWorld()->GetTimerManager().ClearTimer(SetTileEventManagerHandle);
			TileEventManager = NewTileEventManager;
		}
	}
}
