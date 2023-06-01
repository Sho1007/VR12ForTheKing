// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusBoardWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Component/InventoryComponent.h"
#include "../Widget/StatusWidget.h"

void UStatusBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Inventory->OnClicked.AddDynamic(this, &UStatusBoardWidget::InventoryButtonOnClicked);
	Btn_Status->OnClicked.AddDynamic(this, &UStatusBoardWidget::StatusButtonOnClicked);
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
	TB_CurrentHP->SetText(FText::FromString(FString::FromInt(StatusComponent->GetCurrentHP())));

	PB_HP->SetPercent(StatusComponent->GetMaxHP() == 0 ? 0 : (float)StatusComponent->GetCurrentHP() / (float)StatusComponent->GetMaxHP());
	PB_EXP->SetPercent(0);

	TB_AttackPower->SetText(FText::FromString(FString::FromInt(StatusComponent->GetAttackPower())));
	TB_Evasion->SetText(FText::FromString(FString::FromInt(StatusComponent->GetEvasion())));
	TB_Resistance->SetText(FText::FromString(FString::FromInt(StatusComponent->GetResistance())));
	TB_Armor->SetText(FText::FromString(FString::FromInt(StatusComponent->GetArmor())));
	TB_Level->SetText(FText::FromString(FString::FromInt(StatusComponent->GetLevel())));

	TB_Strength->SetText(FText::FromString(FString::FromInt(StatusComponent->GetStrength())));
	TB_Vitality->SetText(FText::FromString(FString::FromInt(StatusComponent->GetVitality())));
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(StatusComponent->GetIntelligence())));
	TB_Cognition->SetText(FText::FromString(FString::FromInt(StatusComponent->GetCognition())));
	TB_Talent->SetText(FText::FromString(FString::FromInt(StatusComponent->GetTalent())));
	TB_Speed->SetText(FText::FromString(FString::FromInt(StatusComponent->GetSpeed())));
	TB_Luck->SetText(FText::FromString(FString::FromInt(StatusComponent->GetLuck())));
}

void UStatusBoardWidget::SetOwnerCharacter(AMyCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;

	UpdateStatus();
}

void UStatusBoardWidget::SetParent(UStatusWidget* NewParentWidget)
{
	checkf(NewParentWidget != nullptr, TEXT("NewParentWidget is not valid"));
	ParentWidget = NewParentWidget;
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
