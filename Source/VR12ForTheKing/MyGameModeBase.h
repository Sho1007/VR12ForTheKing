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

private:
	void CreatePlayer();

	void EndTurn();
	void DoNextTurn();
private:
	// Turn Var
	int CurrentTurn = 0;
	// Move Var
	AHexTile* NextTile;
	bool bIsMoved;
	int32 CurrentMovableCount;
	TArray<bool> MoveJudgeArray;

	// MoveWidget Var
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMoveWidget> MoveWidgetClass;
	UMoveWidget* MoveWidget;

	// HexGridManager Var
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AHexGridManager> HexGridManagerClass;
	AHexGridManager* HexGridManager;

	// Character Var
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AMyCharacter> CharacterClass;


	TArray<AMyPlayerController*> PlayerControllerArray;
	TArray<AMyCharacter*> CharacterArray;
	AMyPlayerController* CurrentPlayer;
	AMyCharacter* CurrentCharacter;
};