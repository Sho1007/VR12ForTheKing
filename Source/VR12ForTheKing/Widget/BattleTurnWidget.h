// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleTurnWidget.generated.h"

/**
 *
 */

class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UBattleTurnWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetTurnArray(const TArray<AMyCharacter*>& NewTurnArray);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void SetTurnImage();
private:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> BasicTurnArray;
};