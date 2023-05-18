// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusWidget.h"

#include "../Component/StatusComponent.h"
#include "StatusBoardWidget.h"

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
