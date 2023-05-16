// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/EventActionButtonWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GamePlayStatics.h"

#include "../MyGameModeBase.h"

void UEventActionButtonWidget::NativeConstruct()
{
	Btn_Action->OnClicked.AddDynamic(this, &UEventActionButtonWidget::ActionButtonOnClicked);
}

void UEventActionButtonWidget::ActionButtonOnClicked()
{
	//UE_LOG(LogTemp, Warning, TEXT("UEventActionButtonWidget::ActionButtonOnClicked : Called"));
	AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(GetWorld()));
	checkf(GameMode != nullptr, TEXT("UEventActionButtonWidget::ActionButtonOnClicked : GameMode is nullptr"));
	GameMode->DoEventAction(TileEventActionType);
}

void UEventActionButtonWidget::SetButtonName(FText NewButtonName)
{
	TB_ActionName->SetText(NewButtonName);
}

void UEventActionButtonWidget::SetButtonType(ETileEventActionType NewButtonType)
{
	TileEventActionType = NewButtonType;
}