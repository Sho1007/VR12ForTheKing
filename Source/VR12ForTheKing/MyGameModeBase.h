// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VR12ForTheKing.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class UHexGridManager;
class AHexTile;
class AMyCharacter;
class AMyPlayerController;
class UMoveWidget;
class UBattleWidget;
class AEventActor;
class UTileEventManager;
class ATileEventMeshCapturor;
class UBattleManagerComponent;
class UMoveManagerComponent;
/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMyGameModeBase();
	virtual void BeginPlay() override;

public:
	void LeftClick(APlayerController* PlayerController);
	void CheckEndTile(AActor* NewActor, APlayerController* TargetPlayerController);
	void CheckFocusActor(AActor* NewActor, APlayerController* TargetPlayerController);
	void CheckTileEvent(AActor* NewActor, APlayerController* TargetPlayerController);

	void SetEndTile(AHexTile* NewEndTile);

	void ReachToTile();

	UFUNCTION(BlueprintCallable)
	void FinishUpdateMoveWidget();

	UFUNCTION(BlueprintCallable)
	UTileEventManager* GetTileEventManager();

	// Event Button Function
	void DoEventAction(ETileEventActionType NewEventActionType);
private:
	void CreatePlayer();
	// Battle Function
	void CalculateTurn();
private:
	// Move Turn Var
	int CurrentTurn = 0;
	// Move Var
	AHexTile* NextTile;
	bool bIsMoved;
	int32 CurrentMovableCount;
	TArray<bool> MoveJudgeArray;

	// Event Var
	AEventActor* CurrentTileEvent = nullptr;
	TArray<AHexTile*> NeighborTileArray;
	int32 MaxSpawnEventCountPerTurn = 3;

	// HexGridManager Var
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UHexGridManager* HexGridManager;

	// EventManager Var
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UTileEventManager* TileEventManager;

	// Character Var
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = true))
	TSubclassOf<AMyCharacter> CharacterClass;

	// Battle Var
	int32 CurrentBattleRound;
	TArray<AMyCharacter*> BattleTurnArray;
	TArray<AMyCharacter*> UseBattleTurnArray;

	// Battle Manager
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UBattleManagerComponent* BattleManager;

	// MoveManager Var
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UMoveManagerComponent* MoveManager;

	TArray<APlayerController*> PlayerControllerArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> CharacterArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> EnemyArray;
	APlayerController* CurrentPlayer;
	AMyCharacter* CurrentCharacter;
};