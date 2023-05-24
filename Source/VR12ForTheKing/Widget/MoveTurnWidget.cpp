// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveTurnWidget.h"
#include "Components/HorizontalBox.h"
#include "MoveTurnWidgetSlot.h"
class UMoveTurnWidgetSlot;
void UMoveTurnWidget::MoveToNextDay(bool IsEndDay)
{
	if (!IsEndDay) return;

	UMoveTurnWidgetSlot* MoveTurnWidgetSlot = Cast<UMoveTurnWidgetSlot>(MoveTurnBox->GetChildAt(0));

	checkf(MoveTurnWidgetSlot != nullptr, TEXT("MoveTurnBox child is not MoveTurnWidgetSlot Class"));

	if (MoveTurnWidgetSlot->IsChaos())
	{
		ChaosCount++;
	}

	for (int i = 0; i < 14; ++i)
	{
		MoveTurnWidgetSlot = Cast<UMoveTurnWidgetSlot>(MoveTurnBox->GetChildAt(i));
		checkf(MoveTurnWidgetSlot != nullptr, TEXT("MoveTurnBox child is not MoveTurnWidgetSlot Class"));
		MoveTurnWidgetSlot->InitWidgetIndex();
	}
}

void UMoveTurnWidget::InitTurnWidget(int32 StartTurnIndex)
{
	for (int i = 0; i < 14; ++i)
	{

	}
}
