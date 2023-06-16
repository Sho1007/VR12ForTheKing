// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "SelectCharacterHUD.generated.h"

/**
 * 
 */
struct FPlayerData;

class USelectCharacterWidget;
UCLASS()
class VR12FORTHEKING_API ASelectCharacterHUD : public AHUD
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void UpdateSelectCharacterWidget(TArray<FPlayerData>& PlayerDataArray);

private:
	USelectCharacterWidget* SelectCharacterWidget;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<USelectCharacterWidget> SelectCharacterWidgetClass;
};
