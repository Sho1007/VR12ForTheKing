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

void UStatusWidget::UpdateStrength(UStatusBoardWidget* TargetBoard, int32 Strength)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetStrengthText(Strength);
}

void UStatusWidget::UpdateVitality(UStatusBoardWidget* TargetBoard, int32 Vitality)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetVitalityText(Vitality);
}

void UStatusWidget::UpdateIntelligence(UStatusBoardWidget* TargetBoard, int32 Intelligence)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetIntelligenceText(Intelligence);
}

void UStatusWidget::UpdateCognition(UStatusBoardWidget* TargetBoard, int32 Cognition)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetCognitionText(Cognition);
}

void UStatusWidget::UpdateTalent(UStatusBoardWidget* TargetBoard, int32 Talent)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetTalentText(Talent);
}

void UStatusWidget::UpdateSpeed(UStatusBoardWidget* TargetBoard, int32 Speed)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetSpeedText(Speed);
}

void UStatusWidget::UpdateLuck(UStatusBoardWidget* TargetBoard, int32 Luck)
{
	if (TargetBoard->GetOwnerCharacter() != WBP_StatusLayout->GetTargetCharacter() || WBP_StatusLayout->GetVisibility() != ESlateVisibility::Visible)
	{
		return;
	}

	WBP_StatusLayout->SetLuckText(Luck);
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