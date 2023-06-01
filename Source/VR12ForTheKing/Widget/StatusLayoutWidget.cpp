// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusLayoutWidget.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Widget/StatusWidget.h"
#include "../Widget/InventoryWidget.h"

void UStatusLayoutWidget::NativeConstruct()
{
	Btn_Close->OnClicked.AddDynamic(this, &UStatusLayoutWidget::CloseButtonOnClicked);
}

void UStatusLayoutWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	if (TargetCharacter != nullptr)
	{
		UStatusComponent* StatusComponent = Cast<UStatusComponent>(TargetCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
		checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));
	}

	TargetCharacter = NewTargetCharacter;

	TB_PlayerName->SetText(TargetCharacter->GetCharacterName());

	UStatusComponent* StatusComponent = Cast<UStatusComponent>(TargetCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));
	StatusComponent->UpdateStrength.BindUFunction(this, FName("SetStrengthText"));
	TB_Strength->SetText(FText::FromString(FString::FromInt(StatusComponent->GetStrength())));

	StatusComponent->UpdateCognition.BindUFunction(this, FName("SetCognitionText"));
	TB_Cognition->SetText(FText::FromString(FString::FromInt(StatusComponent->GetCognition())));

	StatusComponent->UpdateIntelligence.BindUFunction(this, FName("SetIntelligenceText"));
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(StatusComponent->GetIntelligence())));

	StatusComponent->UpdateVitality.BindUFunction(this, FName("SetVitalityText"));
	TB_Vitality->SetText(FText::FromString(FString::FromInt(StatusComponent->GetVitality())));

	StatusComponent->UpdateSpeed.BindUFunction(this, FName("SetSpeedText"));
	TB_Speed->SetText(FText::FromString(FString::FromInt(StatusComponent->GetSpeed())));

	StatusComponent->UpdateTalent.BindUFunction(this, FName("SetTalentText"));
	TB_Talent->SetText(FText::FromString(FString::FromInt(StatusComponent->GetTalent())));

	StatusComponent->UpdateLuck.BindUFunction(this, FName("SetLuckText"));
	TB_Luck->SetText(FText::FromString(FString::FromInt(StatusComponent->GetLuck())));

	TB_PlayerName->SetText(TargetCharacter->GetCharacterName());

	this->SetVisibility(ESlateVisibility::Visible);
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