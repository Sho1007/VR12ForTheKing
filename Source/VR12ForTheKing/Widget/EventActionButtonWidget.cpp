// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EventActionButtonWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GamePlayStatics.h"

#include "../PlayerController/MoveBoardPlayerController.h"

void UEventActionButtonWidget::NativeConstruct()
{
	Btn_Action->OnClicked.AddDynamic(this, &UEventActionButtonWidget::ActionButtonOnClicked);
}

void UEventActionButtonWidget::ActionButtonOnClicked()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("UEventActionButtonWidget::ActionButtonOnClicked")));
	//UE_LOG(LogTemp, Warning, TEXT("UEventActionButtonWidget::ActionButtonOnClicked : Called"));

	AMoveBoardPlayerController* PC = GetWorld()->GetFirstPlayerController<AMoveBoardPlayerController>();
	check(PC);
	PC->DoEventAction(TileEventActionType);
}

void UEventActionButtonWidget::SetButtonName(FText NewButtonName)
{
	TB_ActionName->SetText(NewButtonName);
}

void UEventActionButtonWidget::SetButtonType(ETileEventActionType NewButtonType)
{
	TileEventActionType = NewButtonType;
}