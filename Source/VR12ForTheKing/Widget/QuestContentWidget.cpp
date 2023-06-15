// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/QuestContentWidget.h"

#include "GameFrameWork/GameModeBase.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

#include "../Component/QuestManagerComponent.h"


void UQuestContentWidget::SetDiscription(FText NewDiscription)
{
	TB_QuestPurpose->SetText(NewDiscription);
}

void UQuestContentWidget::InitNewQuest(FName NewQuestID)
{
	QuestID = NewQuestID;
	UQuestManagerComponent* QuestManagerComponent = Cast<UQuestManagerComponent>(GetWorld()->GetAuthGameMode()->FindComponentByClass(UQuestManagerComponent::StaticClass()));
	FQuestNPCData* QuestNPCData = QuestManagerComponent->FindQuestNPCData(QuestID);
	TB_QuestPurpose->SetText(QuestNPCData->Purpose[0].QuestDescription);
	IMG_LeftArrow->SetVisibility(ESlateVisibility::Visible);
}
