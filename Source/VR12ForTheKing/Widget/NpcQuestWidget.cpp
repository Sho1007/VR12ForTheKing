// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/NpcQuestWidget.h"

#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"

#include "GameFramework/GameModeBase.h"

#include "../Component/QuestManagerComponent.h"

void UNpcQuestWidget::InitWidget(FQuestNPCData NewQuestNPCData, int32 QuestStoryIndex, int32 QuestPurposeIndex)
{
	TB_NPCName->SetText(NewQuestNPCData.NpcName);
	TB_NPCNickName->SetText(NewQuestNPCData.NpcNickName);
	IMG_NPC->SetBrushFromTexture(NewQuestNPCData.NpcImage);


	TB_Story->SetText(NewQuestNPCData.StoryDataArray[QuestStoryIndex].GameStory);

	if (NewQuestNPCData.StoryDataArray.Num() - 1 == QuestStoryIndex)
	{
		
		TB_QuestPurpose->SetText(NewQuestNPCData.Purpose[0].QuestDescription);
		TB_QuestPurpose->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TB_QuestPurpose->SetVisibility(ESlateVisibility::Collapsed);
	}
}