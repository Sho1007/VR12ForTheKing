// Fill out your copyright notice in the Description page of Project Settings.


#include "../SelectCharacter/SelectCharacterSlotWidget.h"

#include "Components/Button.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

#include "../../PlayerController/SelectCharacterPlayerController.h"
#include "../../GameState/SelectCharacterGameState.h"

void USelectCharacterSlotWidget::NativeConstruct()
{
	Btn_Select->OnClicked.AddDynamic(this, &USelectCharacterSlotWidget::SelectButtonOnClicked);
	Btn_Cancle->OnClicked.AddDynamic(this, &USelectCharacterSlotWidget::CancleButtonOnClicked);
	Btn_Ready->OnClicked.AddDynamic(this, &USelectCharacterSlotWidget::ReadyButtonOnClicked);
}

void USelectCharacterSlotWidget::SetSlotIndex(int32 NewSlotIndex)
{
	SlotIndex = NewSlotIndex;
}

void USelectCharacterSlotWidget::SetOwnerPlayerIndex(int32 NewOwnerPlayerIndex)
{
	OwnerPlayerIndex = NewOwnerPlayerIndex;
}

void USelectCharacterSlotWidget::Select()
{
	Btn_Select->SetVisibility(ESlateVisibility::Collapsed);
	VB_Customize->SetVisibility(ESlateVisibility::Visible);

	Btn_Cancle->SetVisibility(ESlateVisibility::Visible);
	Btn_Ready->SetVisibility(ESlateVisibility::Visible);
	Btn_Color->SetVisibility(ESlateVisibility::Visible);
	Btn_Class_Left->SetVisibility(ESlateVisibility::Visible);
	Btn_Class_Right->SetVisibility(ESlateVisibility::Visible);
}

void USelectCharacterSlotWidget::Selected()
{
	Btn_Select->SetVisibility(ESlateVisibility::Collapsed);
	VB_Customize->SetVisibility(ESlateVisibility::Visible);

	Btn_Cancle->SetVisibility(ESlateVisibility::Hidden);
	Btn_Ready->SetVisibility(ESlateVisibility::Hidden);
	Btn_Color->SetVisibility(ESlateVisibility::Hidden);
	Btn_Class_Left->SetVisibility(ESlateVisibility::Hidden);
	Btn_Class_Right->SetVisibility(ESlateVisibility::Hidden);
}

void USelectCharacterSlotWidget::Deselect()
{
	Btn_Select->SetVisibility(ESlateVisibility::Visible);
	VB_Customize->SetVisibility(ESlateVisibility::Collapsed);
}

void USelectCharacterSlotWidget::Ready(bool bIsReady)
{
	if (bIsReady)
	{
		TB_Ready->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		TB_Ready->SetVisibility(ESlateVisibility::Hidden);
	}
}

void USelectCharacterSlotWidget::SelectButtonOnClicked()
{
	ASelectCharacterPlayerController* PC = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
	PC->SetPlayerAt(SlotIndex);
}

void USelectCharacterSlotWidget::CancleButtonOnClicked()
{
	ASelectCharacterPlayerController* PC = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
	PC->ResetPlayerAt(SlotIndex);
}

void USelectCharacterSlotWidget::ReadyButtonOnClicked()
{
	ASelectCharacterPlayerController* PC = Cast<ASelectCharacterPlayerController>(GetWorld()->GetFirstPlayerController());
	PC->ReadyPlayerAt(SlotIndex);
}