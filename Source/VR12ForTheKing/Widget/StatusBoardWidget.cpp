// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusBoardWidget.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Widget/StatusWidget.h"

void UStatusBoardWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_Inventory->OnClicked.AddDynamic(this, &UStatusBoardWidget::InventoryButtonOnClicked);
	Btn_Status->OnClicked.AddDynamic(this, &UStatusBoardWidget::StatusButtonOnClicked);
}

void UStatusBoardWidget::UpdateStatus(UStatusComponent* StatusComponent)
{
	FCharacterStatus CharacterStatus = StatusComponent->GetCharacterStatus();


	TB_PlayerName->SetText(OwnerCharacter->GetCharacterName());
	//TB_Gold->SetText();
	TB_CurrentHP;

	PB_HP;
	PB_EXP;

	TB_AttackPower;
	TB_Evasion;
	TB_Resistance;
	TB_Armor;
	TB_Level;

	TB_Strength;
	TB_Vitality;
	TB_Intelligence;
	TB_Cognition;
	TB_Talent;
	TB_Speed;
	TB_Luck;
}

void UStatusBoardWidget::SetOwnerCharacter(AMyCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;

	UStatusComponent* StatusComponent = Cast<UStatusComponent>(OwnerCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("StatusComponent is not valid"));

	UpdateStatus(StatusComponent);
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
