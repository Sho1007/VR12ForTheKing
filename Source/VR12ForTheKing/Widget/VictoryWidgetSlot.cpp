// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/VictoryWidgetSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"






void UVictoryWidgetSlot::SetItmeNameText(FText TargetItemName)
{
	ItemName->SetText(TargetItemName);
}
