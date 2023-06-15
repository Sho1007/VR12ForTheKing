// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestWidget.generated.h"

/**
 * 
 */
class UNpcQuestWidget;
class UQuestOnScreenWidget;
class UQuestEventInfoWidget;

UCLASS()
class VR12FORTHEKING_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	//UFUNCTION(BlueprintCallable)

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UNpcQuestWidget* WBP_NpcQuest;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UQuestEventInfoWidget* WBP_QuestEventInfo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UQuestOnScreenWidget* WBP_QuestOnScreen;

};
