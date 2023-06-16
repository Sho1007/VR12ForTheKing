// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveWidget.h"
#include "../Widget/EventWidget.h"
#include "../Widget/EventInfoWidget.h"

void UMoveWidget::UpdateMoveJudge_Implementation(const TArray<bool>& SuccessArray)
{
}

void UMoveWidget::HideMoveJudgeWidget_Implementation()
{
}

void UMoveWidget::HideWidget()
{
	this->SetVisibility(ESlateVisibility::Collapsed);
}