// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EventInfoWidget.h"

#include "../Event/EventActor.h"
#include "../Event/EnemyEventActor.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UEventInfoWidget::Init(const AEventActor* NewEventActor)
{
	Border_MonsterLevel->SetVisibility(ESlateVisibility::Collapsed);
	Border_MonsterCount->SetVisibility(ESlateVisibility::Collapsed);
	switch (NewEventActor->GetEventType())
	{
	case EEventType::NONE:
		break;
	case EEventType::ENEMY:
		TB_Discription1->SetColorAndOpacity(EnemyDiscriptionColor);
		Border_MonsterLevel->SetVisibility(ESlateVisibility::Visible);
		if (Cast<AEnemyEventActor>(NewEventActor)->GetEnemyNum() > 1)
		{
			Border_MonsterCount->SetVisibility(ESlateVisibility::Visible);
		}
		break;
	case EEventType::STRUCTURE:
		break;
	case EEventType::TOWN:
		TB_Discription1->SetColorAndOpacity(NormalDiscriptionColor);
		break;
	case EEventType::MERCHANT:
		break;
	case EEventType::DUNGEON:
		break;
	}
	TB_EventName->SetText(NewEventActor->GetEventName());
	TB_Discription1->SetText(NewEventActor->GetDiscription1());
}
