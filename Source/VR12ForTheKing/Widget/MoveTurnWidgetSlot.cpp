// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveTurnWidgetSlot.h"
#include "Components/Border.h"
#include "Components/Image.h"
bool UMoveTurnWidgetSlot::IsChaos() const
{
	return bIsChaos;
}

void UMoveTurnWidgetSlot::InitWidgetIndex(int32 NewTurnIndex)
{
	TurnIndex = NewTurnIndex;
	if (TurnIndex % 16 <= 10)
	{
		TurnBorder->SetBrushColor(DayColor);
		
	}
	else
	{
		TurnBorder->SetBrushColor(NightColor);
	
	}

	if (TurnIndex % 8 == 0)
	{
		TurnOnChaos();
	}
	else
	{
		TurnOffChaos();
	}
}

int32 UMoveTurnWidgetSlot::GetTurnIndex() const
{
	return TurnIndex;
}

void UMoveTurnWidgetSlot::TurnOnChaos()
{
	bIsChaos = true;
	ChaosImage->SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UMoveTurnWidgetSlot::TurnOffChaos()
{
	bIsChaos = false;
	ChaosImage->SetVisibility(ESlateVisibility::Collapsed);
}
