// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BattleTurnWidgetSlot.h"
#include "Components/Image.h"
#include "../Character/MyCharacter.h"
void UBattleTurnWidgetSlot::SetImage(UTexture2D* NewImage)
{
	UnitImage->SetBrushFromTexture(NewImage, false);
}

void UBattleTurnWidgetSlot::InitWidget(AMyCharacter* NewCharacter)
{
	MyCharacter = NewCharacter;
	if (MyCharacter == nullptr)
	{
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
	else
	{
		SetImage(MyCharacter->GetCharacterImage());
	}
}

