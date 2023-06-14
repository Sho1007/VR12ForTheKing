// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcQuestWidget.generated.h"

/**
 * 
 */
struct FQuestNPCData;

UCLASS()
class VR12FORTHEKING_API UNpcQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void InitWidget(FQuestNPCData NewQuestNPCData);
};
