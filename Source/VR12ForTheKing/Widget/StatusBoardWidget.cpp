// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusBoardWidget.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"
#include "../Widget/StatusWidget.h"

#include "Kismet/GameplayStatics.h"

void UStatusBoardWidget::UpdateStatus(UStatusComponent* StatusComponent)
{
	FCharacterStatus CharacterStatus = StatusComponent->GetCharacterStatus();
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
