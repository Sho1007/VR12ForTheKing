// Fill out your copyright notice in the Description page of Project Settings.


#include "../Item/GodsBeard.h"

#include "../Character/MyCharacter.h"
#include "../Component/StatusComponent.h"

void AGodsBeard::Use(AMyCharacter* OwnerCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Use God's Beard"), *OwnerCharacter->GetName());

	UStatusComponent* StatusComponent = Cast<UStatusComponent>(OwnerCharacter->FindComponentByClass(UStatusComponent::StaticClass()));
	checkf(StatusComponent != nullptr, TEXT("Owner Character has not StatusComponent"));
	StatusComponent->SetCurrentHP(StatusComponent->GetCurrentHP() + 15);

	this->Destroy();
}