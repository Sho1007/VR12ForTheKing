// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BattleTurnWidget.h"
#include "BattleTurnWidgetSlot.h"
#include "../Character/MyCharacter.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"

void UBattleTurnWidget::SetTurnArray(const TArray<AMyCharacter*>& NewTurnArray)
{

	BasicTurnArray = NewTurnArray;

	InitBattleTurnWidget();
}

void UBattleTurnWidget::InitBattleTurnWidget()
{

	int32 ArrayLength = BasicTurnArray.Num();

	for (int i = 0; i < ArrayLength; ++i)
	{

		UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
		checkf(NewBattleTurnWidgetSlot != nullptr, TEXT("NewBattleTurnWidgetSlot is not created"));
		if (BasicTurnArray[i] != nullptr)
		{
			NewBattleTurnWidgetSlot->InitWidget(BasicTurnArray[i]);
		}
		else if (BasicTurnArray[i] == nullptr)
		{
			NewBattleTurnWidgetSlot->SetVisibility(ESlateVisibility::Collapsed);
		}
		TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
	}



}

void UBattleTurnWidget::MoveToNextTurn(AMyCharacter* NewCharacter)
{

	//UBattleTurnWidgetSlot* FirstBattleTurnWidgetSlot = Cast<UBattleTurnWidgetSlot>(TurnImageArray->GetChildAt(0));
	checkf(TurnImageArray->GetChildAt(0), TEXT("TurnImageArray is empty"));
	UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
	if (NewCharacter != nullptr)
	{
		NewBattleTurnWidgetSlot->InitWidget(NewCharacter);
	}
	TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
	TurnImageArray->GetChildAt(0)->RemoveFromParent();


}

void UBattleTurnWidget::RemoveUnitFromImageArray(int32 Index)
{
	TurnImageArray->GetChildAt(Index)->RemoveFromParent();

}

void UBattleTurnWidget::AddUnitToImageArray(AMyCharacter* NewCharacter, int32 Index)
{
	UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
	NewBattleTurnWidgetSlot->InitWidget(NewCharacter);
	TurnImageArray->InsertChildAt(Index, NewBattleTurnWidgetSlot);
}
