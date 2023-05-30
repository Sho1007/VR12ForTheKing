// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleComponent.h"
#include "../Character/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "StatusComponent.h"
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

const EFactionType& UBattleComponent::GetFactionType() const
{
	return FactionType;
}

const TArray<FName>& UBattleComponent::GetActionArray() const
{
	return ActionArray;
}

void UBattleComponent::BattleAction_Implementation()
{
}

void UBattleComponent::Attack_Implementation()
{
}

void UBattleComponent::MeleeAttack(AMyCharacter* NewCharacter, AMyCharacter* NewUnitTarget)
{

	Character->SetActorRotation(SetCharacterRotation(NewCharacter, NewUnitTarget), ETeleportType::None);
	AMyCharacter* UnitTarget = NewUnitTarget;
	checkf(UnitTarget != nullptr, TEXT("UnitTarget doesnt't exist"));
	Character->SetDestination(UnitTarget->GetActorLocation(), 0.0, 5.0);

}

void UBattleComponent::RangetAttack(AMyCharacter* NewCharacter, AMyCharacter* NewUnitTarget)
{
	Character = NewCharacter;
	Character->SetActorRotation(SetCharacterRotation(NewCharacter, NewUnitTarget), ETeleportType::None);
	CalculateDamage(Character);
	//SpawnActor(); have to spawn projectileclass actor

}

void UBattleComponent::BackToBattlePos(AMyCharacter* NewCharacter)
{
	Character = NewCharacter;
	GoBack = false;
	IsTurnEnd = true;
	Character->SetActorRotation(BattlePosition.GetRotation(), ETeleportType::None);
	// settimerby function name have to be here
	// have to call function that put unit back to array

}

int32 UBattleComponent::CalculateDamage(AMyCharacter* NewCharacter)
{
	Character = NewCharacter;
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(Character->GetComponentByClass(UStatusComponent::StaticClass()));
	int32 Damage = StatusComponent->GetCharacterStatus().AttackPower + 0;// have to put LevelDamage at place of 0
	return 0.0f;
}

void UBattleComponent::ReachToDestination()
{
}

FRotator UBattleComponent::SetCharacterRotation(AMyCharacter* NewCharacter,AMyCharacter* NewUnitTarget)
{
	Character = NewCharacter;
	IsTurnEnd = false;
	Character = Cast<AMyCharacter>(GetOwner());
	checkf(Character != nullptr, TEXT("Character doesnt't exist"));
	AMyCharacter* UnitTarget = NewUnitTarget;
	checkf(UnitTarget != nullptr, TEXT("UnitTarget doesnt't exist"));
	FRotator CharacterRot = UKismetMathLibrary::FindLookAtRotation(Character->GetActorLocation(), UnitTarget->GetActorLocation());
	return CharacterRot;
}
