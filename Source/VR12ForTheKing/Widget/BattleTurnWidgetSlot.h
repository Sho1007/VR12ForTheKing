// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "BattleTurnWidgetSlot.generated.h"

/**
 * 
 */

class UImage;
class UTexture2D;
class AMyCharacter;

UCLASS()
class VR12FORTHEKING_API UBattleTurnWidgetSlot : public UUserWidget
{
	GENERATED_BODY()
public:
	UFUNCTION(BlueprintCallable)
	void SetImage(UTexture2D* NewImage);
	UFUNCTION(BlueprintCallable)
		void InitWidget(AMyCharacter* mycharacter);
	
private:

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
	UImage* UnitImage;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	AMyCharacter* MyCharacter;
};
