// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/QuestWidget.h"

#include "../Widget/NpcQuestWidget.h"
#include "../Widget/QuestEventInfoWidget.h"
#include "../Widget/QuestOnScreenWidget.h"
#include "../Component/QuestManagerComponent.h"



void UQuestWidget::InitNPCQuest(FQuestNPCData* NewQuestNPCData)
{
	QuestNPCData = NewQuestNPCData;
	WBP_NpcQuest->InitWidget(NewQuestNPCData, 0, 0);
}

void UQuestWidget::InitQuestEventInfo(FQuestNPCData* NewQuestNPCData)
{
	QuestNPCData = NewQuestNPCData;
	WBP_QuestEventInfo->InitWidget(FName(*QuestNPCData->Purpose[0].Ojective[0].ObjectID));
}

void UQuestWidget::InitQuestonScreen(FQuestNPCData* NewQuestNPCData)
{
	QuestNPCData = NewQuestNPCData;
	WBP_QuestOnScreen->InitWidget(FName(*QuestNPCData->Purpose[0].Ojective[0].ObjectID));
}


