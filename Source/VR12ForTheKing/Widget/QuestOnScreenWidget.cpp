// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/QuestOnScreenWidget.h"

#include "GameFrameWork/GameModeBase.h"
#include "Components/TextBlock.h"
#include "../Component/QuestManagerComponent.h"
#include "../Widget/QuestContentWidget.h"

void UQuestOnScreenWidget::InitWidget(FName NewQuestID)
{
	QuestID = NewQuestID;
	UQuestManagerComponent* QuestManagerComponent = Cast<UQuestManagerComponent>(GetWorld()->GetAuthGameMode()->FindComponentByClass(UQuestManagerComponent::StaticClass()));
	FQuestNPCData* QuestNPCData = QuestManagerComponent->FindQuestNPCData(QuestID);
	TB_MainQuestName->SetText(QuestNPCData->Purpose[0].QuestName);
	WBP_QuestContent1->SetDiscription(QuestNPCData->Purpose[0].QuestDescription);
	WBP_QuestContent2->SetDiscription(QuestNPCData->Purpose[0].QuestDescription);
	WBP_QuestContent3->SetDiscription(QuestNPCData->Purpose[0].QuestDescription);
}
