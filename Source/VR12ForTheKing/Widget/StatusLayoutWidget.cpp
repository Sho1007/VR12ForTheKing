// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusLayoutWidget.h"

#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Widget/StatusWidget.h"

void UStatusLayoutWidget::NativeConstruct()
{
	Btn_Close->OnClicked.AddDynamic(this, &UStatusLayoutWidget::CloseButtonOnClicked);
}

void UStatusLayoutWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;

	TB_PlayerName->SetText(TargetCharacter->GetCharacterName());

	UStatusComponent* StatusComponent = Cast<UStatusComponent>(TargetCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));
	FCharacterStatus CharacterStatus = StatusComponent->GetCharacterStatus();

	TB_PlayerName->SetText(TargetCharacter->GetCharacterName());

	TB_Strength->SetText(FText::FromString(FString::FromInt(CharacterStatus.Strength)));
	TB_Vitality->SetText(FText::FromString(FString::FromInt(CharacterStatus.Vitality)));
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(CharacterStatus.Intelligence)));
	TB_Cognition->SetText(FText::FromString(FString::FromInt(CharacterStatus.Cognition)));
	TB_Talent->SetText(FText::FromString(FString::FromInt(CharacterStatus.Talent)));
	TB_Speed->SetText(FText::FromString(FString::FromInt(CharacterStatus.Speed)));
	TB_Luck->SetText(FText::FromString(FString::FromInt(CharacterStatus.Luck)));

	this->SetVisibility(ESlateVisibility::Visible);
}

void UStatusLayoutWidget::SwitchToStatus()
{
	WS_Layout->SetActiveWidgetIndex(0);
}

void UStatusLayoutWidget::SwitchToInventory()
{
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
