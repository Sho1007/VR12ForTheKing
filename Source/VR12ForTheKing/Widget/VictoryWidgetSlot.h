// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VictoryWidgetSlot.generated.h"

/**
 * 
 */
class UButton;
class UTextBlock;

UCLASS()
class VR12FORTHEKING_API UVictoryWidgetSlot : public UUserWidget
{
	GENERATED_BODY()

public:


	//Setter,Getter
	void SetItmeNameText(FText TargetItemName);
	

private:

	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* ItemName;
	
};
