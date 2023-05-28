// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/TurnWidget.h"
#include "HeartSlot.h"
#include "Components/HorizontalBox.h"
#include "MoveTurnWidget.h"
#include "CharacterTurnWidget.h"
#include "Components/Image.h"
#include "Components/WidgetSwitcher.h"
#include "Components/TextBlock.h"

void UTurnWidget::Get_Day_Text()
{
	int32 DayCount = WBP_MoveTurnWidget->GetCharacterTurnWidget()->GetDayCount();
	FString DayString;
	DayString = FString::FromInt(DayCount);
	FText DayText;
	DayText = FText::FromString(DayString);

	Day->SetText(DayText);
}

void UTurnWidget::ChaosCount()
{
	int32 ChaosCount = WBP_MoveTurnWidget->GetChaosCount() - 1;
	switch (ChaosCount)
	{
	case 0:
		Chaos1->SetVisibility(ESlateVisibility::Visible);
		break;
	case 1:
		Chaos2->SetVisibility(ESlateVisibility::Visible);
		break;
	case 2:
		Chaos3->SetVisibility(ESlateVisibility::Visible);
		break;
	}

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
	checkf(MoveBattleSwitcher->GetChildAt(1) != nullptr, TEXT("MoveBattleSwitcher doesn't have child"));
	MoveBattleSwitcher->GetChildAt(1);
	MoveBattleSwitcher->SetActiveWidgetIndex(1);
}

void UTurnWidget::ChangetoMoveTurnWidget()
{
	checkf(MoveBattleSwitcher->GetChildAt(0) != nullptr, TEXT("MoveBattleSwitcher doesn't have child"));
	MoveBattleSwitcher->GetChildAt(0);
	MoveBattleSwitcher->SetActiveWidgetIndex(0);
}

void UTurnWidget::InitWidget()
{
	WBP_MoveTurnWidget->InitTurnWidget();
	//
}