// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusWidget.h"

#include "../Component/StatusComponent.h"
#include "StatusBoardWidget.h"
#include "StatusLayoutWidget.h"

bool UStatusWidget::UpdateStatusBoard(int BoardIndex, UStatusComponent* StatusComponent)
{
	switch (BoardIndex)
	{
	case 1:
		WBP_StatusBoard1->UpdateStatus(StatusComponent);
		break;
	}
	return true;
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