// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MyGameModeBase.generated.h"

class AHexGridManager;
class AHexTile;
class AMyCharacter;
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

private:
	void CreateHexGrid();
	void CreatePlayer();
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AHexGridManager> HexGridManagerClass;
	AHexGridManager* HexGridManager;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AHexTile> HexTileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AMyCharacter> CharacterClass;
	TArray<AMyCharacter*> CharacterArray;

	int CurrentCharacterIndex = 0;
};