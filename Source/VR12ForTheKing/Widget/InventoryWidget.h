// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventoryWidget.generated.h"

/**
 * 
 */
class AMyCharacter;
class UVerticalBox;
UCLASS()
class VR12FORTHEKING_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(AMyCharacter* NewTargetCharacter);

private:
	AMyCharacter* TargetCharacter;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UVerticalBox* VB_ItemList;
};
