// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "NpcQuestWidget.generated.h"

/**
 * 
 */
struct FQuestNPCData;

class UTextBlock;
class UImage;
class UButton;
class UWidgetSwitcher;

UCLASS()
class VR12FORTHEKING_API UNpcQuestWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	//UFUNCTION(BlueprintCallable)
	void InitWidget(FQuestNPCData* NewQuestNPCData, int32 QuestStoryIndex, int32 QuestPurposeIndex);




private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UButton* BTN_ClickContinue;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UButton* BTN_NpcQuestWidget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UImage* IMG_NPC;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_NPCName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_NPCNickName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_QuestPurpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UTextBlock* TB_Story;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true, BindWidget))
		UWidgetSwitcher* WidgetSwitcher_QuestStoryandPurpose;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		FName QuestID;
};
