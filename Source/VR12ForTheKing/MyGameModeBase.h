// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VR12ForTheKing.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AHexGridManager;
class AHexTile;
class AMyCharacter;
class AMyPlayerController;
class UMoveWidget;
class UBattleWidget;
class AEventActor;
class ATileEventManager;
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
	// Getter / Setter

	AHexGridManager* GetHexGridManager() const;

	void SetStartTile(AHexTile* NewStartTile);
	void SetEndTile(AHexTile* NewEndTile);

	void MoveCharacter();

	void ReachToTile();

	const AMyPlayerController* GetCurrentPlayer() const;
	const bool GetIsMoved() const;

	UFUNCTION(BlueprintCallable)
	void FinishUpdateMoveWidget();

	// Event Widget
	UFUNCTION(BlueprintCallable)
	void HideEventInfoWidget();
	
	UFUNCTION(BlueprintCallable)
	void InitAndShowEventInfoWidget(AEventActor* NewEventActor, FVector2D WidgetPos);

	UFUNCTION(BlueprintCallable)
	ATileEventManager* GetTileEventManager();

	// Event Button Function
	void DoEventAction(ETileEventActionType NewEventActionType);
private:
	void CreatePlayer();

	void EndTurn();
	void DoNextTurn();

	// Event Fucntion
	void SpawnEvent();
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

	// MoveWidget Var
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMoveWidget> MoveWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UMoveWidget* MoveWidget;

	// Event Var
	AEventActor* CurrentTileEvent = nullptr;
	TArray<AHexTile*> NeighborTileArray;
	int32 MaxSpawnEventCountPerTurn = 3;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<ATileEventMeshCapturor> TileEventMeshCapturorClass;
	ATileEventMeshCapturor* TileEventMeshCapturor;

	// BattleWidget Var
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBattleWidget> BattleWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UBattleWidget* BattleWidget;


	// HexGridManager Var
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AHexGridManager> HexGridManagerClass;
	AHexGridManager* HexGridManager;

	// EventManager Var
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<ATileEventManager> TileEventManagerClass;
	ATileEventManager* TileEventManager;

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

	TArray<AMyPlayerController*> PlayerControllerArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> CharacterArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> EnemyArray;
	AMyPlayerController* CurrentPlayer;
	AMyCharacter* CurrentCharacter;
};