// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EventWidget.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"
#include "Components/UniformGridPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "../Event/EventActor.h"
#include "EventActionButtonWidget.h"

void UEventWidget::InitWidget(const AEventActor* NewEventActor)
{
	FEventInfo EventInfo = NewEventActor->GetEventInfo();
	Txt_EventName->SetText(EventInfo.EventName);
	Txt_Discription1->SetText(EventInfo.Discription1);
	Txt_Discription2->SetText(EventInfo.Discription2);

	checkf(EventActionButtonClass != nullptr, TEXT("UEventWidget::InitWidget : EventActionButtonClass is nullptr"));
	for (int i = 0; i < EventInfo.EventActionButtonArray.Num(); ++i)
	{
		UEventActionButtonWidget* Button = CreateWidget<UEventActionButtonWidget>(GetWorld(), EventActionButtonClass);
		Button->SetButtonName(EventInfo.EventActionButtonArray[i].ButtonName);
		Button->SetButtonType(EventInfo.EventActionButtonArray[i].TileEventActionType);
		UGP_ActionButtonArray->AddChildToUniformGrid(Button, i/4, i%4);
	}

	if (EventInfo.EventType == EEventType::ENEMY)
	{
		Brd_EnemyLevel->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Brd_EnemyLevel->SetVisibility(ESlateVisibility::Collapsed);
	}
}