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

	for (int j = 0; j < 2; j++)// SetTurnArray twice
	{
		for (int i = 0; i < ArrayLength; ++i) 
		{
			
			UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
			checkf(NewBattleTurnWidgetSlot != nullptr, TEXT("NewBattleTurnWidgetSlot is not created"));

			
			NewBattleTurnWidgetSlot->InitWidget(BasicTurnArray[i]);
			TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
		}
	}
	

}

void UBattleTurnWidget::MoveToNextTurn(AMyCharacter* NewCharacter)
{

	UBattleTurnWidgetSlot* FirstBattleTurnWidgetSlot = Cast<UBattleTurnWidgetSlot>(TurnImageArray->GetChildAt(0));
	checkf(TurnImageArray->GetChildAt(0), TEXT("TurnImageArray is empty"));
	UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
	NewBattleTurnWidgetSlot->InitWidget(NewCharacter);
	TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
	TurnImageArray->GetChildAt(0)->RemoveFromParent();


}
