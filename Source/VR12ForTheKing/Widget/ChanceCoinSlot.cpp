// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/ChanceCoinSlot.h"
#include "Components/Border.h"
#include "Components//WidgetSwitcher.h"

void UChanceCoinSlot::SetImage(UTexture2D* NewImage)
{
	CoinEmpty->SetBrushFromTexture(NewImage);
}

void UChanceCoinSlot::SetSwitchCoinImage(int32 SwitcherIndex)
{
	ChanceCoinSwitcher->SetActiveWidgetIndex(SwitcherIndex);
}

UTexture2D* UChanceCoinSlot::GetCoinImageFromArray(int32 CoinImageIndex)
{
	checkf(CoinImageIndex < CoinImageArray.Num(), TEXT("CoinImageArray Out of Size"));
	return CoinImageArray[CoinImageIndex];
}
