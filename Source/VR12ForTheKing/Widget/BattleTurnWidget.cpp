// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BattleTurnWidget.h"

void UBattleTurnWidget::SetTurnArray(const TArray<AMyCharacter*>& NewTurnArray)
{
	BasicTurnArray = NewTurnArray;

	SetTurnImage();
}

void UBattleTurnWidget::SetTurnImage_Implementation()
{
}
