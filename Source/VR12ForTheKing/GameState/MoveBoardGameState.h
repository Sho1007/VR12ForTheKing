// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "GameFramework/GameStateBase.h"
#include "MoveBoardGameState.generated.h"

/**
 * 
 */
class AMyCharacter;
class UMoveManagerComponent;
class UHexGridManager;
class UBattleManagerComponent;
class UTileEventManager;
class AHexTile;

struct FAction;
UCLASS()
class VR12FORTHEKING_API AMoveBoardGameState : public AGameStateBase
{
	GENERATED_BODY()

protected:
	AMoveBoardGameState(const FObjectInitializer& ObjectInitializer);
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	// Move
	AMyCharacter* GetCurrentTurnCharacter();
	void InitGameState();
	void SetReadyPlayer();
	void MoveCharacter(APlayerController* TargetPlayerController);
	void ReachToTile();

	// Event
	void DoEventAction(APlayerController* TargetPlayerController, ETileEventActionType NewEventActionType);

	// Battle
	UFUNCTION(NetMulticast, Reliable)
	void ChangeToBattleWidget();
	void ChangeToBattleWidget_Implementation();

	void RemoveDeadUnitFromArray(AMyCharacter* DeadCharacter);

	// Turn
	void MoveToNextTurn();

public:
	// Getter / Setter
	void SetEndTile(APlayerController* NewPlayerController, AHexTile* NewEndTile);
	int32 GetControllerID(APlayerController* TargetPlayerController);

	FAction* GetBattleAction(FName TargetActionName);
private:
	void StartGame();
	void SetNextTurn();
	void CreatePlayerCharacter();
	

private:
	bool bIsInit;
	bool bIsLoaded;

	UPROPERTY(meta = (AllowPrivateAccess = true))
		int32 ReadyPlayerCount;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<AMyCharacter> CharacterClass;
	UPROPERTY(meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> PlayerCharacterArray;
	AMyCharacter* CurrentTurnCharacter;
	int32 CharacterIndex;

	// Component
	UPROPERTY(Replicated, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UMoveManagerComponent* MoveManagerComponent;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UHexGridManager* HexGridManagerComponet;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UBattleManagerComponent* BattleManager;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UTileEventManager* TileEventManager;
};