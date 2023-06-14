// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/BattleTurnWidget.h"
#include "BattleTurnWidgetSlot.h"
#include "../Character/MyCharacter.h"
#include "Components/HorizontalBox.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"

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

		if (BasicTurnArray[i] != nullptr) // show basicturnarray on log when initalize
		{
			UE_LOG(LogTemp, Warning, TEXT("TurnImageArray %s"), *BasicTurnArray[i]->GetName());
		}
		else if (BasicTurnArray[i] == nullptr)
		{
			UE_LOG(LogTemp, Warning, TEXT("TurnImageArray Null"));
		}

	
	}

	UE_LOG(LogTemp, Warning, TEXT("TurnImageArrayNum %d"), TurnImageArray->GetChildrenCount());

}

void UBattleTurnWidget::MoveToNextTurn(AMyCharacter* NewCharacter)
{

	//UBattleTurnWidgetSlot* FirstBattleTurnWidgetSlot = Cast<UBattleTurnWidgetSlot>(TurnImageArray->GetChildAt(0));
	checkf(TurnImageArray->GetChildrenCount() != 0, TEXT("TurnImageArray is empty"));
	UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
	if (NewCharacter != nullptr)
	{
		NewBattleTurnWidgetSlot->InitWidget(NewCharacter);
		TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
		TurnImageArray->GetChildAt(0)->RemoveFromParent();
	}
	if (NewCharacter == nullptr)
	{
		NewBattleTurnWidgetSlot->SetVisibility(ESlateVisibility::Collapsed);
		TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
		TurnImageArray->GetChildAt(0)->RemoveFromParent();
	}



}

void UBattleTurnWidget::RemoveUnitFromImageArray(int32 RemoveIndex)
{
	checkf(TurnImageArray->GetChildrenCount() > RemoveIndex, TEXT("TurnImageArray is empty"));
	TurnImageArray->GetChildAt(RemoveIndex)->RemoveFromParent();
	UE_LOG(LogTemp, Warning, TEXT("TurnImageArrayNum %d"), TurnImageArray->GetChildrenCount());
}

void UBattleTurnWidget::AddUnitToImageArray(TArray<AMyCharacter*>& NewTurnArray)
{
	TurnImageArray->ClearChildren();

	for (int i = 0; i < NewTurnArray.Num(); ++i)
	{
		UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
		NewBattleTurnWidgetSlot->InitWidget(NewTurnArray[i]);

		TurnImageArray->AddChildToHorizontalBox(NewBattleTurnWidgetSlot);
	}

	/*UBattleTurnWidgetSlot* NewBattleTurnWidgetSlot = CreateWidget<UBattleTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), BattleTurnWidgetSlotClass);
	NewBattleTurnWidgetSlot->InitWidget(NewCharacter);

	UE_LOG(LogTemp, Warning, TEXT("InsertImage at %d"), InsertIndex);*/
}
