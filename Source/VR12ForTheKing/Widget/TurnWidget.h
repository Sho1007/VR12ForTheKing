// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TurnWidget.generated.h"

/**
 * 
 */

class UMoveTurnWidget;
class UBattleTurnWidget;
UCLASS()
class VR12FORTHEKING_API UTurnWidget : public UUserWidget
{
	GENERATED_BODY()
	

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBattleTurnWidget* WBP_BattleTurnWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UMoveTurnWidget* WBP_MoveTurnWidget;
};
