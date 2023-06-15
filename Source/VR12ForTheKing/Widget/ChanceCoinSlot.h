// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ChanceCoinSlot.generated.h"

/**
 * 
 */
class UBorder;
UCLASS()
class VR12FORTHEKING_API UChanceCoinSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UBorder* Coin;
	
};
