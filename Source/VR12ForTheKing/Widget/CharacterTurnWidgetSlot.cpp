// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/CharacterTurnWidgetSlot.h"
#include "Components/SizeBox.h"

void UCharacterTurnWidgetSlot::SetSizeBig()
{

	CharacterSizeBox->SetWidthOverride(BaseSize*SizeModifier);
	CharacterSizeBox->SetHeightOverride(BaseSize * SizeModifier);
}

void UCharacterTurnWidgetSlot::SetSizeSmall()
{

	CharacterSizeBox->SetWidthOverride(BaseSize);
	CharacterSizeBox->SetHeightOverride(BaseSize);
}
