// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/ChanceCoinSlot.h"
#include "Components/Border.h"

void UChanceCoinSlot::SetImage(UTexture2D* NewImage)
{
	Coin->SetBrushFromTexture(NewImage);
}
