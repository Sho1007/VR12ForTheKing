// Fill out your copyright notice in the Description page of Project Settings.


#include "../GameState/MoveBoardGameState.h"

#include "Net/UnrealNetwork.h"
#include "GameFramework/PlayerState.h"
#include "Kismet/GamePlayStatics.h"

#include "LevelSequence.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

#include "../PlayerController/MoveBoardPlayerController.h"
#include "../Character/MyCharacter.h"
#include "../Component/MoveManagerComponent.h"
#include "../Component/BattleManagerComponent.h"
#include "../Event/TileEventManager.h"
#include "../HexGrid/HexGridManager.h"
#include "../HexGrid/HexTile.h"
#include "../GameMode/MoveBoardGameMode.h"
#include "../HUD/MoveBoardHUD.h"

AMoveBoardGameState::AMoveBoardGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsInit = false;
	bIsLoaded = false;
	bIsStarted = false;
	ReadyPlayerCount = 0;

	MoveManagerComponent = CreateDefaultSubobject<UMoveManagerComponent>(FName(TEXT("MoveManagerComponent")));
	check(MoveManagerComponent);

	HexGridManagerComponet = CreateDefaultSubobject<UHexGridManager>(FName(TEXT("HexGridManagerComponet")));
	check(HexGridManagerComponet);

	BattleManager = CreateDefaultSubobject<UBattleManagerComponent>(TEXT("BattleManager"));
	check(BattleManager != nullptr);

	TileEventManager = CreateDefaultSubobject<UTileEventManager>(TEXT("TileEventManager"));
	check(TileEventManager != nullptr);
}

void AMoveBoardGameState::BeginPlay()
{
	Super::BeginPlay();

	if (bIsInit == false)
	{
		bIsInit = true;
		InitGameState();
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ALevelSequenceActor::StaticClass(), LevelSequenceActorArray);
	}
}

void AMoveBoardGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMoveBoardGameState, MoveManagerComponent);
}

void AMoveBoardGameState::CreatePlayerCharacter(APlayerController* TargetController)
{
	// Create Player Character with Player Data
	// Todo : Set SpawnPosition
	check(CharacterClass != nullptr);
	AMyCharacter* NewPlayerCharacter = GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, FVector(0, 0, 100), FRotator(0,0,0));
	FCharacterData* NewCharacterData = new FCharacterData();
	NewCharacterData->ControllerIndex = GetControllerID(TargetController);
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("PlayerController Index : %d"), GetControllerID(TargetController)));
	NewPlayerCharacter->InitPlayerCharacter(NewCharacterData);

	PlayerCharacterArray.Add(NewPlayerCharacter);
}
void AMoveBoardGameState::PlaySequence()
{
	//LevelSequenceActor = Cast<ALevelSequenceActor>(LevelSequenceActorArray[0]);
	//LevelSequenceActor->GetSequencePlayer()->Play();
	if (!GEngine) return;
	if (HasAuthority())
	{
		FQualifiedFrameTime EndTime = Cast<ALevelSequenceActor>(LevelSequenceActorArray[0])->GetSequencePlayer()->GetEndTime();
		BattleManager->OnEndSequence(EndTime.AsSeconds());
	}
	Cast<ALevelSequenceActor>(LevelSequenceActorArray[0])->GetSequencePlayer()->Play();
	
}
void AMoveBoardGameState::InitGameState()
{
	if (HasAuthority())
	{
		HexGridManagerComponet->CreateGrid();
	}
}

void AMoveBoardGameState::SetReadyPlayer()
{
	ReadyPlayerCount++;

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("AMoveBoardGameState::OnRep_ReadyPlayerCount : PlayerCount : %d, PlayerArrayNum : %d"), ReadyPlayerCount, PlayerArray.Num()));

	if (ReadyPlayerCount == 3)
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Red, FString::Printf(TEXT("AMoveBoardGameState::OnRep_ReadyPlayerCount : Ready to Play")));
		StartGame();
	}
}

void AMoveBoardGameState::MoveCharacter_Implementation(APlayerController* TargetPlayerController)
{
	if (MoveManagerComponent->IsMoved()) return;
	int32 NewControllerIndex = GetControllerID(TargetPlayerController);
	if (NewControllerIndex == MoveManagerComponent->GetCurrentTurnCharacter()->GetControllerIndex())
	{
		MoveManagerComponent->MoveCharacter();
	}
}

void AMoveBoardGameState::ReachToTile()
{
	MoveManagerComponent->ReachToDestination();
}

void AMoveBoardGameState::DoEventAction(APlayerController* TargetPlayerController, ETileEventActionType NewEventActionType)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("AMoveBoardGameState::DoEventAction")));
	if (MoveManagerComponent->GetCurrentTurnCharacter()->GetControllerIndex() != GetControllerID(TargetPlayerController)) return;

	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Cyan, FString::Printf(TEXT("AMoveBoardGameState::DoEventAction")));
	switch (NewEventActionType)
	{
		
	case ETileEventActionType::Battle:
		ChangeToBattleWidget();
		for (int i = 0; i < PlayerCharacterArray.Num(); ++i)
		{
			PlayerCharacterArray[i]->SetMoveMode(false);
		}

		// Fix : NexTile Maybe nullptr
		if (MoveManagerComponent->GetNextTile() == nullptr)
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("AMoveBoardGameState::DoEventAction : NextTile is Null")));
		}
		
		BattleManager->InitBattle(MoveManagerComponent->GetNextTile());
		break;
	case ETileEventActionType::Retreat:
		break;
	}
}

void AMoveBoardGameState::ChangeToBattleWidget_Implementation()
{
	AMoveBoardHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMoveBoardHUD>();
	HUD->ChangeToBattleWidget();
}

void AMoveBoardGameState::DoBattleAction(FName ActionName, AMyCharacter* DeadPlayer)
{
	BattleManager->DoBattleAction(ActionName, DeadPlayer);
}

void AMoveBoardGameState::DoBattleActionWork()
{
	BattleManager->DoBattleActionWork();
}

void AMoveBoardGameState::RemoveDeadUnitFromArray(AMyCharacter* DeadCharacter)
{
	BattleManager->RemoveDeadUnitFromArray(DeadCharacter);
}

void AMoveBoardGameState::MoveToNextTurn()
{
	BattleManager->MoveToNextUnitTurn();
}

void AMoveBoardGameState::SetEndTile(APlayerController* NewPlayerController, AHexTile* NewEndTile)
{
	if (!bIsStarted || MoveManagerComponent->IsMoved()) return;
	int32 NewControllerIndex = GetControllerID(NewPlayerController);
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("AMoveBoardGameState::SetEndTile %d, %d"), NewControllerIndex, CurrentTurnCharacter->GetControllerIndex()));
	if (MoveManagerComponent->GetCurrentTurnCharacter()->GetControllerIndex() == NewControllerIndex)
	{
		HexGridManagerComponet->SetEndTile(NewEndTile, MoveManagerComponent->GetMovableCount());
	}
}

int32 AMoveBoardGameState::GetControllerID(APlayerController* TargetPlayerController)
{
	for (int i = 0; i < PlayerArray.Num(); ++i)
	{
		if (PlayerArray[i]->GetPlayerController() == TargetPlayerController)
		{
			return i;
		}
	}
	return -1;
}

AMoveBoardPlayerController* AMoveBoardGameState::GetPlayerController(int32 ControllerIndex)
{
	if (ControllerIndex < 0 || ControllerIndex >= PlayerArray.Num()) return nullptr;

	return Cast<AMoveBoardPlayerController>(PlayerArray[ControllerIndex]->GetPlayerController());
}

FAction* AMoveBoardGameState::GetBattleAction(FName TargetActionName)
{
	if (TargetActionName.IsNone()) return nullptr;
	return TileEventManager->FindActionInfo(TargetActionName);
}

AMyCharacter* AMoveBoardGameState::GetBattleTurnCharacter() const
{
	return BattleManager->GetCurrentTurnCharacter();
}

void AMoveBoardGameState::StartGame()
{
	bIsStarted = true;
	MoveManagerComponent->Init(PlayerCharacterArray);
	for (int i = 0; i < PlayerCharacterArray.Num(); ++i)
	{
		PlayerCharacterArray[i]->SetCurrentTile(HexGridManagerComponet->GetTile(2, 8));
	}
	MoveManagerComponent->StartTurn();
}