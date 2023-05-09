// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveWidget.h"
#include "../Widget/EventWidget.h"

void UMoveWidget::UpdateMoveJudge_Implementation(const TArray<bool>& SuccessArray)
{
}

void UMoveWidget::HideMoveJudgeWidget_Implementation()
{
}

void UMoveWidget::HideEventWidget()
{
	if (WBP_Event)
	{
		WBP_Event->SetVisibility(ESlateVisibility::Collapsed);
	}
}