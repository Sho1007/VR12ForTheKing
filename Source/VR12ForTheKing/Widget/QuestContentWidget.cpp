// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/QuestContentWidget.h"

#include "Components/TextBlock.h"

void UQuestContentWidget::SetDiscription(FText NewDiscription)
{
	TB_QuestPurpose->SetText(NewDiscription);
}
