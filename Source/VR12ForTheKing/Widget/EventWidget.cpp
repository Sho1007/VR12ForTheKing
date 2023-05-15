// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EventWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "../Event/EventActor.h"

void UEventWidget::InitWidget(const AEventActor* NewEventActor)
{
	FEventInfo EventInfo = NewEventActor->GetEventInfo();
	Txt_EventName->SetText(EventInfo.EventName);
	Txt_Discription1->SetText(EventInfo.Discription1);
	Txt_Discription2->SetText(EventInfo.Discription2);
	if (EventInfo.EventType == EEventType::ENEMY)
	{
		Brd_EnemyLevel->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Brd_EnemyLevel->SetVisibility(ESlateVisibility::Collapsed);
	}
}