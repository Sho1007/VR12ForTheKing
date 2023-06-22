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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	void Init(const TArray<AMyCharacter*>& NewPlayerCharacterArray);

	int32 GetMovableCount() const;

	void StartTurn();
	void MoveCharacter();
	void ReachToDestination();

	AHexTile* GetNextTile() const;
private:
	UFUNCTION(NetMulticast, Reliable)
	void TestMulticast();
	void TestMulticast_Implementation();

	UFUNCTION(NetMulticast, Reliable)
	void HideMoveJudgeWidget();
	void HideMoveJudgeWidget_Implementation();

	void PrepareTurn();
	void ExecuteTurn();
	void FinishTurn();

	void CheckMoveCount();

	UFUNCTION()
	void OnRep_MoveJudgeArray();
public:
	// Getter / Setter
	const bool IsMoved() const;

	AMyCharacter* GetCurrentTurnCharacter() const;

private:
	void SetNextTurn();
private:
	TArray<AMyCharacter*> PlayerCharacterArray;
	int32 CurrentTurnIndex;
	AMyCharacter* CurrentTurnCharacter;

	UHexGridManager* HexGridManager;

	int32 Turn;
	int32 Day;

	UPROPERTY(Replicated, meta = (AllowPrivateAccess = true))
	int32 MovableCount;
	UPROPERTY(ReplicatedUsing = OnRep_MoveJudgeArray, meta = (AllowPrivateAccess = true))
	TArray<bool> MoveJudgeArray;

	AHexTile* NextTile;

	bool bIsMoved = true;
};