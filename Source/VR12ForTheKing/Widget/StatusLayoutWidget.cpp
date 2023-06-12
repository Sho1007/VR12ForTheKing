// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusLayoutWidget.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Component/InventoryComponent.h"
#include "../Widget/StatusWidget.h"
#include "../Widget/InventoryWidget.h"

void UStatusLayoutWidget::NativeConstruct()
{
	Btn_Close->OnClicked.AddDynamic(this, &UStatusLayoutWidget::CloseButtonOnClicked);
}

void UStatusLayoutWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;

	TB_PlayerName->SetText(TargetCharacter->GetCharacterName());

	// Status
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(TargetCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));

	TB_Strength->SetText(FText::FromString(FString::FromInt(StatusComponent->GetStrength())));
	TB_Cognition->SetText(FText::FromString(FString::FromInt(StatusComponent->GetCognition())));
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(StatusComponent->GetIntelligence())));
	TB_Vitality->SetText(FText::FromString(FString::FromInt(StatusComponent->GetVitality())));
	TB_Speed->SetText(FText::FromString(FString::FromInt(StatusComponent->GetSpeed())));
	TB_Talent->SetText(FText::FromString(FString::FromInt(StatusComponent->GetTalent())));
	TB_Luck->SetText(FText::FromString(FString::FromInt(StatusComponent->GetLuck())));

	this->SetVisibility(ESlateVisibility::Visible);
}

void UStatusLayoutWidget::UpdateWidget(AMyCharacter* NewTargetCharacter)
{
	if (TargetCharacter != NewTargetCharacter || this->GetVisibility() != ESlateVisibility::Visible) return;

	InitWidget(NewTargetCharacter);
	WBP_Inventory->InitWidget(TargetCharacter);
}

void UStatusLayoutWidget::SwitchToStatus()
{
	WS_Layout->SetActiveWidgetIndex(0);
}

void UStatusLayoutWidget::SwitchToInventory()
{
	WBP_Inventory->InitWidget(TargetCharacter);
	WS_Layout->SetActiveWidgetIndex(1);
}

void UStatusLayoutWidget::SetParent(UStatusWidget* NewParentWidget)
{
	ParentWidget = NewParentWidget;
	WBP_Inventory->SetParent(ParentWidget);
}

AMyCharacter* UStatusLayoutWidget::GetTargetCharacter() const
{
	return TargetCharacter;
}

int32 UStatusLayoutWidget::GetActiveWidgetIndex() const
{
	return WS_Layout->GetActiveWidgetIndex();
}

void UStatusLayoutWidget::CloseButtonOnClicked()
{
	SetVisibility(ESlateVisibility::Collapsed);
}

void UStatusLayoutWidget::SetStrengthText(int32 NewStrength)
{
	TB_Strength->SetText(FText::FromString(FString::FromInt(NewStrength)));
}

void UStatusLayoutWidget::SetVitalityText(int32 NewVitality)
{

	TB_Vitality->SetText(FText::FromString(FString::FromInt(NewVitality)));
}

void UStatusLayoutWidget::SetIntelligenceText(int32 NewIntelligence)
{
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(NewIntelligence)));
}

void UStatusLayoutWidget::SetCognitionText(int32 NewCognition)
{
	TB_Cognition->SetText(FText::FromString(FString::FromInt(NewCognition)));
}

void UStatusLayoutWidget::SetTalentText(int32 NewTalent)
{
	TB_Talent->SetText(FText::FromString(FString::FromInt(NewTalent)));
}

void UStatusLayoutWidget::SetSpeedText(int32 NewSpeed)
{
	TB_Speed->SetText(FText::FromString(FString::FromInt(NewSpeed)));
}

void UStatusLayoutWidget::SetLuckText(int32 NewLuck)
{
	TB_Luck->SetText(FText::FromString(FString::FromInt(NewLuck)));
}