// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleManagerComponent.h"

#include "../Character/MyCharacter.h"

// Sets default values for this component's properties
UBattleManagerComponent::UBattleManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UBattleManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UBattleManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UBattleManagerComponent::AddEnemyClass(const TSubclassOf<AMyCharacter> NewEnemyClass)
{
	EnemyClassArray.Add(NewEnemyClass);
}

void UBattleManagerComponent::AddPlayerCharacter(AMyCharacter* NewPlayerCharacter)
{
	PlayerCharacterArray.Add(NewPlayerCharacter);
}

void UBattleManagerComponent::DebugInfo()
{
	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::DebugInfo : Player"));
	for (auto Iter : PlayerCharacterArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Iter->GetName());
	}

	UE_LOG(LogTemp, Warning, TEXT("UBattleManagerComponent::DebugInfo : Enemy"));
	for (auto Iter : EnemyClassArray)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *Iter->GetName());
	}
}
