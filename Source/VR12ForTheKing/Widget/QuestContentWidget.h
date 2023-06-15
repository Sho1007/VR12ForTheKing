// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestContentWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class VR12FORTHEKING_API UQuestContentWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetDiscription(FText NewDiscription);
	
private:
	UPROPERTY(meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_QuestPurpose;
};
