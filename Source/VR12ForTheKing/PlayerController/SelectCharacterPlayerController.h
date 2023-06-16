// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SelectCharacterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API ASelectCharacterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	ASelectCharacterPlayerController(const FObjectInitializer& ObjectInitializer);
	
	virtual void BeginPlay() override;
public:
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void SetPlayerAt(int32 SlotIndex);
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ResetPlayerAt(int32 SlotIndex);
	UFUNCTION(BlueprintCallable, Server, Reliable)
	void ReadyPlayerAt(int32 SlotIndex);

protected:
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void SpawnDefaultHUD() override;
public:
	// Getter / Setter
	void SetPlayerIndex(int32 NewPlayerIndex);
	int32 GetPlayerIndex() const;

private:
	UFUNCTION()
	void OnRep_PlayerIndex();
private:
	UPROPERTY(ReplicatedUsing = OnRep_PlayerIndex, meta = (AllowPrivateAccess = true))
	int32 PlayerIndex;
};