// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/QuestEventInfoWidget.h"

#include "GameFramework/GameModeBase.h"
#include "Components/TextBlock.h"

#include "../Component/QuestManagerComponent.h"

void UQuestEventInfoWidget::InitWidget(FName NewQuestID)
{
	QuestID = NewQuestID;
	UQuestManagerComponent* QuestManagerComponent = Cast<UQuestManagerComponent>(GetWorld()->GetAuthGameMode()->FindComponentByClass(UQuestManagerComponent::StaticClass()));
	FQuestNPCData* QuestNPCData = QuestManagerComponent->FindQuestNPCData(QuestID);
	TB_QuestPurpose->SetText(QuestNPCData->Purpose[0].QuestDescription);
}
