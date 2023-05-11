// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleComponent.h"

// Sets default values for this component's properties
UBattleComponent::UBattleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UBattleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBattleComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBattleComponent::SetFactionType(EFactionType NewFactionType)
{
	FactionType = NewFactionType;
}

bool UBattleComponent::Action_Implementation()
{
	return false;
}

bool UBattleComponent::Attack_Implementation()
{
	return false;
}

