// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusWidget.h"

#include "../Component/StatusComponent.h"
#include "StatusBoardWidget.h"
#include "StatusLayoutWidget.h"

bool UStatusWidget::UpdateStatusBoard(int BoardIndex)
{
	switch (BoardIndex)
	{
	case 1:
		WBP_StatusBoard1->UpdateStatus();
		break;
	}
	return true;
}

void UStatusWidget::HideWidget()
{
	WBP_StatusLayout->SetVisibility(ESlateVisibility::Collapsed);
}

void UStatusWidget::OpenInventory(AMyCharacter* TargetCharacter)
{
	if (WBP_StatusLayout->GetVisibility() == ESlateVisibility::Visible &&
		WBP_StatusLayout->GetTargetCharacter() == TargetCharacter &&
		WBP_StatusLayout->GetActiveWidgetIndex() == 1)
	{
		WBP_StatusLayout->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	WBP_StatusLayout->InitWidget(TargetCharacter);

	WBP_StatusLayout->SwitchToInventory();
	WBP_StatusLayout->SetVisibility(ESlateVisibility::Visible);
}

void UStatusWidget::OpenStatus(AMyCharacter* TargetCharacter)
{
	if (WBP_StatusLayout->GetVisibility() == ESlateVisibility::Visible &&
		WBP_StatusLayout->GetTargetCharacter() == TargetCharacter &&
		WBP_StatusLayout->GetActiveWidgetIndex() == 0)
	{
		WBP_StatusLayout->SetVisibility(ESlateVisibility::Collapsed);
		return;
	}

	WBP_StatusLayout->InitWidget(TargetCharacter);

	WBP_StatusLayout->SwitchToStatus();
	WBP_StatusLayout->SetVisibility(ESlateVisibility::Visible);
}

void UStatusWidget::SetParentToChild()
{
	WBP_StatusBoard1->SetParent(this);
	WBP_StatusBoard2->SetParent(this);
	WBP_StatusBoard3->SetParent(this);
	WBP_StatusLayout->SetParent(this);
}

void UStatusWidget::SetOwnerCharacter(const TArray<AMyCharacter*>& NewCharacterArray)
{
	if (NewCharacterArray.Num() > 0)
	{
		WBP_StatusBoard1->SetOwnerCharacter(NewCharacterArray[0]);
	}
	else
	{
		WBP_StatusBoard1->SetVisibility(ESlateVisibility::Hidden);
	}
	if (NewCharacterArray.Num() > 1)
	{
		WBP_StatusBoard2->SetOwnerCharacter(NewCharacterArray[1]);
	}
	else
	{
		WBP_StatusBoard2->SetVisibility(ESlateVisibility::Hidden);
	}
	if (NewCharacterArray.Num() > 2)
	{
		WBP_StatusBoard3->SetOwnerCharacter(NewCharacterArray[2]);
	}
	else
	{
		WBP_StatusBoard3->SetVisibility(ESlateVisibility::Hidden);
	}
}