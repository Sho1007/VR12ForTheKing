// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Engine/DataTable.h"


#include "QuestWidget.generated.h"


/**
 * 
 */
struct FQuestNPCData;

class UNpcQuestWidget;
class UQuestOnScreenWidget;
class UQuestEventInfoWidget;

UCLASS()
class VR12FORTHEKING_API UQuestWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//UFUNCTION(BlueprintCallable)
		void InitNPCQuest(FQuestNPCData* NewQuestNPCData);
	//UFUNCTION(BlueprintCallable)
		void InitQuestEventInfo(FQuestNPCData* NewQuestNPCData);
	//UFUNCTION(BlueprintCallable)
		void InitQuestonScreen(FQuestNPCData* NewQuestNPCData);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		UNpcQuestWidget* WBP_NpcQuest;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		UQuestEventInfoWidget* WBP_QuestEventInfo;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		UQuestOnScreenWidget* WBP_QuestOnScreen;
	//UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
		FQuestNPCData* QuestNPCData;
};
