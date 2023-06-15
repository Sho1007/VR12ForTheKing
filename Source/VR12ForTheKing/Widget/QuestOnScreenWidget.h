// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestOnScreenWidget.generated.h"

/**
 * 
 */
class UQuestContentWidget;
class UTextBlock;
class UVerticalBox;

UCLASS()
class VR12FORTHEKING_API UQuestOnScreenWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
		void InitWidget(FName NewQuestID);
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		UQuestContentWidget* WBP_QuestContent1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		UQuestContentWidget* WBP_QuestContent2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		UQuestContentWidget* WBP_QuestContent3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_MainQuestName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UVerticalBox* VB_QuestContent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		FName QuestID;
};
