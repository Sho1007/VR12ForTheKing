// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveWidget.h"
#include "../Widget/EventWidget.h"
#include "../Widget/EventInfoWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanelSlot.h"

void UMoveWidget::UpdateMoveJudge_Implementation(const TArray<bool>& SuccessArray)
{
}

void UMoveWidget::HideMoveJudgeWidget_Implementation()
{
}

void UMoveWidget::ShowEventWidget()
{
	UE_LOG(LogTemp, Warning, TEXT("UMoveWidget::ShowEventWidget : Called"));
	checkf(WBP_Event != NULL, TEXT("UMoveWidget::ShowEventWidget : Event Widget is not valid"));
	WBP_Event->SetVisibility(ESlateVisibility::Visible);
}

void UMoveWidget::InitEventWidget(const AEventActor* NewEventActor)
{
	WBP_Event->InitWidget(NewEventActor);
}

void UMoveWidget::HideEventWidget()
{
	checkf(WBP_Event != NULL, TEXT("UMoveWidget::HideEventWidget : Event Widget is not valid"));
	WBP_Event->SetVisibility(ESlateVisibility::Collapsed);
}

void UMoveWidget::ShowEventInfoWidget(FVector2D NewPos)
{
	UWidgetLayoutLibrary::SlotAsCanvasSlot(WBP_EventInfo)->SetPosition(NewPos);
	WBP_EventInfo->SetVisibility(ESlateVisibility::Visible);
}

void UMoveWidget::HideEventInfoWidget()
{
	checkf(WBP_EventInfo != NULL, TEXT("UMoveWidget::HideEventInfoWidget : Event Info Widget is not valid"));
	WBP_EventInfo->SetVisibility(ESlateVisibility::Collapsed);
}

void UMoveWidget::InitEventInfoWidget(const AEventActor* NewEventActor)
{
	WBP_EventInfo->Init(NewEventActor);
}