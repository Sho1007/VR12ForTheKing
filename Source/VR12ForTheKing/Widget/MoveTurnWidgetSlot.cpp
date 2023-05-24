// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveTurnWidgetSlot.h"
#include "Components/Border.h"
#include "Components/Image.h"
bool UMoveTurnWidgetSlot::IsChaos() const
{
	return bIsChaos;
}

void UMoveTurnWidgetSlot::InitWidgetIndex()
{
	ChaosIndex = (ChaosIndex + 1) % 16;
	CurrentTurnIndex = (CurrentTurnIndex + 1) % 15;
	
	if (CurrentTurnIndex <= 9)
	{
		TurnBorder->SetBrushColor(DayColor);
	}
	else
	{
		TurnBorder->SetBrushColor(NightColor);
	}

	 TurnOnChaos(ChaosIndex);
}

void UMoveTurnWidgetSlot::TurnOnChaos(int32 NewChaosIndex)
{
	if (NewChaosIndex % 8 == 0)
	{
		ChaosImage->SetVisibility(ESlateVisibility::Visible);
		bIsChaos = true;
	}
	else
	{
		ChaosImage->SetVisibility(ESlateVisibility::Collapsed);
		bIsChaos = false;
	}
}
