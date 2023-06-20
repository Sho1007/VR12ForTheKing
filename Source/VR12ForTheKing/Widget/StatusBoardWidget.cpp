// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusBoardWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Component/InventoryComponent.h"
#include "../Widget/StatusWidget.h"
#include "../Widget/InventorySlotButton.h"
#include "../Character/MyPlayerController.h"

#include "../PlayerController/MoveBoardPlayerController.h"

void UStatusBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Inventory->OnClicked.AddDynamic(this, &UStatusBoardWidget::InventoryButtonOnClicked);
	Btn_Status->OnClicked.AddDynamic(this, &UStatusBoardWidget::StatusButtonOnClicked);

	InventorySlotArray.Add(Btn_InvenSlot0);
	InventorySlotArray.Add(Btn_InvenSlot1);
	InventorySlotArray.Add(Btn_InvenSlot2);
	InventorySlotArray.Add(Btn_InvenSlot3);
	InventorySlotArray.Add(Btn_InvenSlot4);
	InventorySlotArray.Add(Btn_InvenSlot5);
	InventorySlotArray.Add(Btn_InvenSlot6);
	InventorySlotArray.Add(Btn_InvenSlot7);
	InventorySlotArray.Add(Btn_InvenSlot8);
	InventorySlotArray.Add(Btn_InvenSlot9);
}

FReply UStatusBoardWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}

void UStatusBoardWidget::UpdateStatus()
{
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(OwnerCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("StatusComponent is not valid"));
	
	UInventoryComponent* InventoryComponent = Cast<UInventoryComponent>(OwnerCharacter->GetComponentByClass(UInventoryComponent::StaticClass()));
	checkf(InventoryComponent != nullptr, TEXT("InventoryComponent is not valid"));
	TB_Gold->SetText(FText::FromString(FString::FromInt(InventoryComponent->GetCurrentGold())));
	
	TB_PlayerName->SetText(OwnerCharacter->GetCharacterName());
	
	StatusComponent->UpdateCurrentHP.BindUFunction(this, FName("UpdateCurrentHP"));
	UpdateCurrentHP(StatusComponent->GetCurrentHP());

	// Todo Bind ProgressBar [HP / EXP]

	StatusComponent->UpdateAttackPower.BindUFunction(this, FName("UpdateAttackPower"));
	UpdateAttackPower(StatusComponent->GetAttackPower());

	StatusComponent->UpdateEvasion.BindUFunction(this, FName("UpdateEvasion"));
	UpdateEvasion(StatusComponent->GetEvasion());
	
	StatusComponent->UpdateResistance.BindUFunction(this, FName("UpdateResistance"));
	UpdateResistance(StatusComponent->GetResistance());
	
	StatusComponent->UpdateArmor.BindUFunction(this, FName("UpdateArmor"));
	UpdateArmor(StatusComponent->GetArmor());

	StatusComponent->UpdateLevel.BindUFunction(this, FName("UpdateLevel"));
	UpdateLevel(StatusComponent->GetLevel());

	StatusComponent->UpdateStrength.BindUFunction(this, FName("UpdateStrength"));
	UpdateStrength(StatusComponent->GetStrength());

	StatusComponent->UpdateVitality.BindUFunction(this, FName("UpdateVitality"));
	UpdateVitality(StatusComponent->GetVitality());
	
	StatusComponent->UpdateIntelligence.BindUFunction(this, FName("UpdateIntelligence"));
	UpdateIntelligence(StatusComponent->GetIntelligence());
	
	StatusComponent->UpdateCognition.BindUFunction(this, FName("UpdateCognition"));
	UpdateCognition(StatusComponent->GetCognition());
	
	StatusComponent->UpdateTalent.BindUFunction(this, FName("UpdateTalent"));
	UpdateTalent(StatusComponent->GetTalent());
	
	StatusComponent->UpdateSpeed.BindUFunction(this, FName("UpdateSpeed"));
	UpdateSpeed(StatusComponent->GetSpeed());
	
	StatusComponent->UpdateLuck.BindUFunction(this, FName("UpdateLuck"));
	UpdateLuck(StatusComponent->GetLuck());
}

void UStatusBoardWidget::UpdateInventory()
{
	TArray<FItemInstance>& ItemArray = OwnerInventory->GetItemArray();

	UE_LOG(LogTemp, Warning, TEXT("UpdateInventory is Called : %d"), ItemArray.Num());

	int32 SlotIndex = 0;

	for (int i = 0; i < ItemArray.Num(); ++i)
	{
		FName ItemRow = ItemArray[i].ItemRow;
		FItem* ItemInfo = OwnerInventory->GetItemInfo(ItemRow);
		if (ItemInfo->ItemType != EItemType::CONSUMABLE) continue;
		InventorySlotArray[SlotIndex]->InitWidget(OwnerInventory, i);
		InventorySlotArray[SlotIndex++]->SetVisibility(ESlateVisibility::Visible);
		if (SlotIndex == 10) break;
	}

	for (; SlotIndex < 10; ++SlotIndex)
	{
		InventorySlotArray[SlotIndex]->SetVisibility(ESlateVisibility::Hidden);
	}

	ParentWidget->UpdateLayoutWidget(OwnerCharacter);
}

void UStatusBoardWidget::SetOwnerCharacter(AMyCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;

	OwnerInventory = Cast<UInventoryComponent>(NewOwnerCharacter->FindComponentByClass(UInventoryComponent::StaticClass()));

	checkf(OwnerInventory != nullptr, TEXT("Owner has not Inventory Component"));

	OwnerInventory->UpdateInventory.BindUFunction(this, FName(TEXT("UpdateInventory")));

	UpdateStatus();
	UpdateInventory();
}

AMyCharacter* UStatusBoardWidget::GetOwnerCharacter() const
{
	return OwnerCharacter;
}

void UStatusBoardWidget::SetParent(UStatusWidget* NewParentWidget)
{
	checkf(NewParentWidget != nullptr, TEXT("NewParentWidget is not valid"));
	ParentWidget = NewParentWidget;

	for (int i = 0; i < InventorySlotArray.Num(); ++i)
	{
		InventorySlotArray[i]->NativeConstruct(ParentWidget);
	}
}

void UStatusBoardWidget::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Mouse Enterd in %s"), *this->GetName());

	AMoveBoardPlayerController* PC = GetWorld()->GetFirstPlayerController<AMoveBoardPlayerController>();
	if (PC)
	{
		PC->SetIsOnWidget(true);
	}
	// Todo : Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->SetIsOnWidget(true);
}

void UStatusBoardWidget::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	UE_LOG(LogTemp, Warning, TEXT("Mouse Leaved in %s"), *this->GetName());

	AMoveBoardPlayerController* PC = GetWorld()->GetFirstPlayerController<AMoveBoardPlayerController>();
	if (PC)
	{
		PC->SetIsOnWidget(false);
	}
	// Todo : Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController())->SetIsOnWidget(false);
}

void UStatusBoardWidget::InventoryButtonOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s InventoryButton Clicked"), *OwnerCharacter->GetName());
	ParentWidget->OpenInventory(OwnerCharacter);
}

void UStatusBoardWidget::StatusButtonOnClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("%s StatusButton Clicked"), *OwnerCharacter->GetName());
	ParentWidget->OpenStatus(OwnerCharacter);
}

void UStatusBoardWidget::UpdateCurrentHP(int32 CurrentHP)
{
	TB_CurrentHP->SetText(FText::FromString(FString::FromInt(CurrentHP)));
}

void UStatusBoardWidget::UpdateAttackPower(int32 AttackPower)
{
	TB_AttackPower->SetText(FText::FromString(FString::FromInt(AttackPower)));
}

void UStatusBoardWidget::UpdateEvasion(int32 Evasion)
{
	TB_Evasion->SetText(FText::FromString(FString::FromInt(Evasion)));
}

void UStatusBoardWidget::UpdateResistance(int32 Resistance)
{
	TB_Resistance->SetText(FText::FromString(FString::FromInt(Resistance)));
}

void UStatusBoardWidget::UpdateArmor(int32 Armor)
{
	TB_Armor->SetText(FText::FromString(FString::FromInt(Armor)));
}

void UStatusBoardWidget::UpdateLevel(int32 Level)
{
	TB_Level->SetText(FText::FromString(FString::FromInt(Level)));
}

void UStatusBoardWidget::UpdateStrength(int32 Strength)
{
	TB_Strength->SetText(FText::FromString(FString::FromInt(Strength)));
	ParentWidget->UpdateStrength(this, Strength);
}

void UStatusBoardWidget::UpdateVitality(int32 Vitality)
{
	TB_Vitality->SetText(FText::FromString(FString::FromInt(Vitality)));
	ParentWidget->UpdateVitality(this, Vitality);
}

void UStatusBoardWidget::UpdateIntelligence(int32 Intelligence)
{
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(Intelligence)));
	ParentWidget->UpdateIntelligence(this, Intelligence);
}

void UStatusBoardWidget::UpdateCognition(int32 Cognition)
{
	TB_Cognition->SetText(FText::FromString(FString::FromInt(Cognition)));
	ParentWidget->UpdateCognition(this, Cognition);
}

void UStatusBoardWidget::UpdateTalent(int32 Talent)
{
	TB_Talent->SetText(FText::FromString(FString::FromInt(Talent)));
	ParentWidget->UpdateTalent(this, Talent);
}

void UStatusBoardWidget::UpdateSpeed(int32 Speed)
{
	TB_Speed->SetText(FText::FromString(FString::FromInt(Speed)));
	ParentWidget->UpdateSpeed(this, Speed);
}

void UStatusBoardWidget::UpdateLuck(int32 Luck)
{
	TB_Luck->SetText(FText::FromString(FString::FromInt(Luck)));
	ParentWidget->UpdateLuck(this, Luck);
}