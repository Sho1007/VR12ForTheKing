// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AHexGridManager;
class AHexTile;
class AMyCharacter;
class AMyPlayerController;
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

	void MoveCharacter();

	const AMyPlayerController* GetCurrentPlayer() const;
	const bool GetIsMoved() const;

private:
	void CreatePlayer();

	void DoNextTurn();
private:
	// Turn Var
	int CurrentTurn = 0;
	// Move Var
	bool bIsMoved;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AHexGridManager> HexGridManagerClass;
	AHexGridManager* HexGridManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AMyCharacter> CharacterClass;

	TArray<AMyPlayerController*> PlayerControllerArray;
	TArray<AMyCharacter*> CharacterArray;
	AMyPlayerController* CurrentPlayer;
	AMyCharacter* CurrentCharacter;
};