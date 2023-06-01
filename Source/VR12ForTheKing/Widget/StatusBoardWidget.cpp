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
}

void UStatusBoardWidget::UpdateVitality(int32 Vitality)
{
	TB_Vitality->SetText(FText::FromString(FString::FromInt(Vitality)));
}

void UStatusBoardWidget::UpdateIntelligence(int32 Intelligence)
{
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(Intelligence)));
}

void UStatusBoardWidget::UpdateCognition(int32 Cognition)
{
	TB_Cognition->SetText(FText::FromString(FString::FromInt(Cognition)));
}

void UStatusBoardWidget::UpdateTalent(int32 Talent)
{
	TB_Talent->SetText(FText::FromString(FString::FromInt(Talent)));
}

void UStatusBoardWidget::UpdateSpeed(int32 Speed)
{
	TB_Speed->SetText(FText::FromString(FString::FromInt(Speed)));
}

void UStatusBoardWidget::UpdateLuck(int32 Luck)
{
	TB_Luck->SetText(FText::FromString(FString::FromInt(Luck)));
}