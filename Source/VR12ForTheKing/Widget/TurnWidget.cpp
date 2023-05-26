// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/TurnWidget.h"
#include "HeartSlot.h"
#include "Components/HorizontalBox.h"
class UCharacterTurnWidget;
FText UTurnWidget::Get_Day_Text()
{
	

	return FText();
}

void UTurnWidget::ChaosCount()
{
}

void UTurnWidget::AddHeartCount()
{
	UHeartSlot* NewHeartSlot = CreateWidget<UHeartSlot>(GetWorld()->GetFirstPlayerController(), HeartSlotClass);
	HeartBox->AddChildToHorizontalBox(NewHeartSlot);
	
}

void UTurnWidget::DeleteHeartCount()
{
	int32 HeartNum = HeartBox->GetChildrenCount() - 1;
	HeartBox->RemoveChildAt(HeartNum);
}

void UTurnWidget::OpenSettion()
{
}

void UTurnWidget::TurnOver()
{
}

void UTurnWidget::ChangetoBattleTurnWidget()
{
}

void UTurnWidget::ChangetoMoveTurnWidget()
{
}
