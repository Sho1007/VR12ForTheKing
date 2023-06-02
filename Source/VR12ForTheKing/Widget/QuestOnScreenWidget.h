// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestOnScreenWidget.generated.h"

/**
 * 
 */
class UQuestContentWidget;

UCLASS()
class VR12FORTHEKING_API UQuestOnScreenWidget : public UUserWidget
{
	GENERATED_BODY()
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UQuestContentWidget* WBP_QuestContent1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UQuestContentWidget* WBP_QuestContent2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UQuestContentWidget* WBP_QuestContent3;
};
