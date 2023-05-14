// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AMyGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

public:

	void SetStartTile(AHexTile* NewStartTile);
	void SetEndTile(AHexTile* NewEndTile);

	void CheckMoveCount();
	void MoveCharacter();

	void ReachToTile();

	const AMyPlayerController* GetCurrentPlayer() const;
	const bool GetIsMoved() const;

	UFUNCTION(BlueprintCallable)
	void FinishUpdateMoveWidget();

	UFUNCTION(BlueprintCallable)
	void CreateMoveWidget();

	// Event Widget
	UFUNCTION(BlueprintCallable)
	void HideEventInfoWidget();
	
	UFUNCTION(BlueprintCallable)
	void InitAndShowEventInfoWidget(AEventActor* NewEventActor, FVector2D WidgetPos);

	UFUNCTION(BlueprintCallable)
	ATileEventManager* GetTileEventManager();

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
	TArray<AHexTile*> NeighborTileArray;
	int32 MaxSpawnEventCountPerTurn = 3;

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


	TArray<AMyPlayerController*> PlayerControllerArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> CharacterArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> EnemyArray;
	AMyPlayerController* CurrentPlayer;
	AMyCharacter* CurrentCharacter;
};