// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FSoundData : public FTableRowBase
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	USoundBase* SoundAsset;
};

class AMyCharacter;
struct FItem;
struct FAction;
UCLASS()
class VR12FORTHEKING_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);
	virtual void Init() override;
public:
	void AddPlayerController(APlayerController* NewPlayerController);
	int32 FindPlayerControllerIndex(APlayerController* TargetPlayerController);

	void PlaySound2D(FName SoundName);

	FItem* FindItem(FName ItemRow);
	FAction* FindAction(FName ActionRow);
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UDataTable* SoundDataTable;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UDataTable* ItemDataTable;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UDataTable* ActionDataTable;
	
	TArray<APlayerController*> PlayerControlelrArray;
};