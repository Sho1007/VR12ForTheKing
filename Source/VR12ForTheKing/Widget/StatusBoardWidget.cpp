// Fill out your copyright notice in the Description page of Project Settings.


#include "../Widget/StatusBoardWidget.h"
#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"

void UStatusBoardWidget::UpdateStatus(UStatusComponent* StatusComponent)
{
	//PlayerMaxHP = StatusComponent->GetMaxHP();
}

void UStatusBoardWidget::SetOwnerCharacter(AMyCharacter* NewOwnerCharacter)
{
	OwnerCharacter = NewOwnerCharacter;

	UStatusComponent* StatusComponent = Cast<UStatusComponent>(OwnerCharacter->GetComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("StatusComponent is not valid"));

	UpdateStatus(StatusComponent);
}