// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/CharacterTurnWidget.h"
#include "Components/HorizontalBox.h"
#include "CharacterTurnWidgetSlot.h"

class UCharacterTurnWidgetSlot;
void UCharacterTurnWidget::InitWidget()
{
	UCharacterTurnWidgetSlot* CharacterTurnWidgetSlot = Cast<UCharacterTurnWidgetSlot>(CharacterTurnBox->GetChildAt(CurrentIndex));
	checkf(CharacterTurnWidgetSlot != nullptr, TEXT("CharacterTurnBox child is not CharacterTurnWidgetSlot Class"));
	CharacterTurnWidgetSlot->SetSizeBig();


}

bool UCharacterTurnWidget::IsEndDay()
{
	return bIsEndDay;
}

bool UCharacterTurnWidget::UpdateWidget()
{
	UCharacterTurnWidgetSlot* CharacterTurnWidgetSlot = Cast<UCharacterTurnWidgetSlot>(CharacterTurnBox->GetChildAt(CurrentIndex));
	checkf(CharacterTurnWidgetSlot != nullptr, TEXT("CharacterTurnBox child is not CharacterTurnWidgetSlot Class"));
	CharacterTurnWidgetSlot->SetSizeSmall();
	CurrentIndex = (CurrentIndex + 1) % 3;
	CharacterTurnWidgetSlot = Cast<UCharacterTurnWidgetSlot>(CharacterTurnBox->GetChildAt(CurrentIndex));
	checkf(CharacterTurnWidgetSlot != nullptr, TEXT("CharacterTurnBox child is not CharacterTurnWidgetSlot Class"));
	CharacterTurnWidgetSlot->SetSizeBig();
	if (CurrentIndex == 0)
	{
		DayCount++;
		bIsNewDay = true;
		return bIsNewDay;
	}
	else
	{
		bIsNewDay = false;
		return bIsNewDay;
	}
}
