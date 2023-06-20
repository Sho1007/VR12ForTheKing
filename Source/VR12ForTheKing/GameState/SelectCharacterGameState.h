// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Net/UnrealNetwork.h"
#include "GameFramework/GameStateBase.h"
#include "SelectCharacterGameState.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FPlayerData
{
	GENERATED_BODY()
	
public:
	FPlayerData(int32 NewControllerIndex = -1) : ControllerIndex(NewControllerIndex), bIsReady(false)
	{
	}
	
	UPROPERTY()
	int32 ControllerIndex;
	UPROPERTY()
	bool bIsReady;
};

DECLARE_DELEGATE_OneParam(FDele_UpdatePlayerData, TArray<FPlayerData>&)

class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API ASelectCharacterGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	ASelectCharacterGameState();

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable)
	void SetPlayer(int32 SlotIndex, int32 PlayerIndex);
	UFUNCTION(Server, Reliable)
	void ResetPlayer(int32 SlotIndex);

	void ReadyPlayer(int32 SlotIndex, bool bIsReady);
	bool GetReadyAt(int32 SlotIndex) const;
	
private:
	bool CheckAllReady() const;

	UFUNCTION()
	void OnRep_PlayerDataArray();

public:
	FDele_UpdatePlayerData UpdatePlayerData;
private:
	UPROPERTY(EditInstanceOnly, ReplicatedUsing = OnRep_PlayerDataArray, meta = (AllowPrivateAccess = true))
	TArray<FPlayerData> PlayerDataArray;
	UPROPERTY(EditInstanceOnly, Replicated, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> PlayerCharacterArray;
};