// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusLayoutWidget.h"

#include "Components/TextBlock.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Widget/StatusWidget.h"

void UStatusLayoutWidget::InitWidget(AMyCharacter* NewTargetCharacter)
{
	TargetCharacter = NewTargetCharacter;

	TB_PlayerName->SetText(TargetCharacter->GetCharacterName());

	UStatusComponent* StatusComponent = Cast<UStatusComponent>(TargetCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Character has not StatusComponent"));
	FCharacterStatus CharacterStatus = StatusComponent->GetCharacterStatus();

	TB_Strength->SetText(FText::FromString(FString::FromInt(CharacterStatus.Strength)));
	TB_Vitality->SetText(FText::FromString(FString::FromInt(CharacterStatus.Vitality)));
	TB_Intelligence->SetText(FText::FromString(FString::FromInt(CharacterStatus.Intelligence)));
	TB_Cognition->SetText(FText::FromString(FString::FromInt(CharacterStatus.Cognition)));
	TB_Talent->SetText(FText::FromString(FString::FromInt(CharacterStatus.Talent)));
	TB_Speed->SetText(FText::FromString(FString::FromInt(CharacterStatus.Speed)));
	TB_Luck->SetText(FText::FromString(FString::FromInt(CharacterStatus.Luck)));

	this->SetVisibility(ESlateVisibility::Visible);
}

void UStatusLayoutWidget::SetParent(UStatusWidget* NewParentWidget)
{
	ParentWidget = NewParentWidget;
}
