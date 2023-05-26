// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/MoveTurnWidget.h"
#include "Components/HorizontalBox.h"
#include "MoveTurnWidgetSlot.h"

// 
void UMoveTurnWidget::MoveToNextDay(bool IsEndDay)
{
	if (!IsEndDay) return;

	checkf(MoveTurnBox->GetChildrenCount() > 0, TEXT("MoveTurnBox is Empty"));
	 MoveTurnWidgetSlot = Cast<UMoveTurnWidgetSlot>(MoveTurnBox->GetChildAt(0));
	checkf(MoveTurnWidgetSlot != nullptr, TEXT("MoveTurnBox child is not MoveTurnWidgetSlot Class"));
	// 첫번째 자식이 카오스면 카오스 게이지 1올려주기
	if ((MoveTurnWidgetSlot->IsChaos()) == true)
	{
		ChaosCount++;
	}

	// 마지막 자식을 켜줍니다.
	 UMoveTurnWidgetSlot* LastSlot = Cast<UMoveTurnWidgetSlot>(MoveTurnBox->GetChildAt(14));
	 checkf(LastSlot != nullptr, TEXT("LastSlot does not exist"));
	 LastSlot->SetVisibility(ESlateVisibility::HitTestInvisible);

	 // 첫번째 자식과 같은 상태로 마지막에 새로 만들어 추가해줍니다.
	 UMoveTurnWidgetSlot* FirstSlot = Cast<UMoveTurnWidgetSlot>(MoveTurnBox->GetChildAt(0));
	 checkf(FirstSlot != nullptr, TEXT("FirstSlot does not exist"));
	 UMoveTurnWidgetSlot* NewSlot = CreateWidget<UMoveTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), MoveTurnWidgetSlotClass);
	 NewSlot->InitWidgetIndex(LastSlot->GetTurnIndex() + 1);
	 MoveTurnBox->AddChildToHorizontalBox(NewSlot);

	 // 마지막 자식을 꺼줍니다.
	 MoveTurnBox->GetChildAt(15)->SetVisibility(ESlateVisibility::Collapsed);

	 // 첫번째 자식을 떨굽니다.
	 MoveTurnBox->GetChildAt(0)->RemoveFromParent();
	/*	for (int i = 0; i < 15; i++)
		{
		{
			
			UMoveTurnWidgetSlot* LastMoveTurnSlot = Cast<UMoveTurnWidgetSlot>(MoveTurnBox->GetChildAt(i));
			checkf(MoveTurnWidgetSlot != nullptr, TEXT("MoveTurnBox child is not MoveTurnWidgetSlot Class"));
			if (i == 14)
			LastMoveTurnSlot->InitWidgetIndex();
		}*/

}

void UMoveTurnWidget::InitTurnWidget(int32 StartTurnIndex)
{
	checkf(MoveTurnWidgetSlotClass != nullptr, TEXT("MoveTurnWidgetSlotClass doesn't exist"));

	for (int i = 0; i < 15; ++i)
	{
		UMoveTurnWidgetSlot* NewMoveTurntSlot = CreateWidget<UMoveTurnWidgetSlot>(GetWorld()->GetFirstPlayerController(), MoveTurnWidgetSlotClass);
		checkf(NewMoveTurntSlot != nullptr, TEXT("MoveTurnWidgetSlot is not created"));

		NewMoveTurntSlot->InitWidgetIndex(StartTurnIndex + i);
		MoveTurnBox->AddChildToHorizontalBox(NewMoveTurntSlot);
	}
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("MoveTurnBoxSize : %d"), MoveTurnBox->GetChildrenCount()));
	MoveTurnBox->GetChildAt(14)->SetVisibility(ESlateVisibility::Collapsed);
	//GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, FString::Printf(TEXT("%d"), MoveTurnBox->GetChildrenCount()));
}
