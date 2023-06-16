// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveManagerComponent.generated.h"

class AMyCharacter;
class UMoveWidget;
class UHexGridManager;
class ATileEventManager;
class AMyPlayerController;
class AHexTile;
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UMoveManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	void Init();

	int32 GetMovableCount() const;

	void StartTurn();
	void MoveCharacter();
	void ReachToDestination();

	AHexTile* GetNextTile() const;
private:
	void PrepareTurn();
	void ExecuteTurn();
	void FinishTurn();

	void CheckMoveCount();
public:
	// Getter / Setter
	const bool IsMoved() const;
	const AMyPlayerController* GetCurrentController() const;
	void SetPlayerCharacterArray(const TArray<AMyCharacter*>& NewPlayerCharacterArray);
	void SetPlayerControllerArray(const TArray<AMyPlayerController*>& NewPlayerControllerArray);
private:
	UHexGridManager* HexGridManager;

	int32 Turn;
	int32 Day;

	AMyCharacter* CurrentCharacter;
	AMyPlayerController* CurrentController;
	TArray<AMyCharacter*> PlayerCharacterArray;
	TArray<AMyPlayerController*> PlayerControllerArray;

	int32 MovableCount;
	TArray<bool> MoveJudgeArray;

	AHexTile* NextTile;

	bool bIsMoved = true;
};