// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveManagerComponent.generated.h"

class AMyCharacter;
class UMoveWidget;
class UHexGridManager;
class ATileEventManager;
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
private:
	void CreateMoveWidget();

	void PrepareTurn();
	void ExecuteTurn();
	void FinishTurn();

	void CheckMoveCount();
	void MoveCharacter();
public:
	// Getter / Setter
	const bool IsMoved() const;
	const APlayerController* GetCurrentController() const;
	const UMoveWidget* GetMoveWidget() const;
	void SetPlayerCharacterArray(const TArray<AMyCharacter*>& NewPlayerCharacterArray);
	void SetPlayerControllerArray(const TArray<APlayerController*>& NewPlayerControllerArray);
private:
	UHexGridManager* HexGridManager;
	ATileEventManager* TileEventManager;

	UFUNCTION()
	void SetTileEventManager();
	FTimerHandle SetTileEventManagerHandle;

	int32 Turn;
	int32 Day;

	AMyCharacter* CurrentCharacter;
	APlayerController* CurrentController;
	TArray<AMyCharacter*> PlayerCharacterArray;
	TArray<APlayerController*> PlayerControllerArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMoveWidget> MoveWidgetClass;
	UMoveWidget* MoveWidget;

	int32 MovableCount;
	TArray<bool> MoveJudgeArray;

	bool bIsMoved = false;
};