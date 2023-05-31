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

void UBattleComponent::SetActionTarget(AMyCharacter* NewActionTarget)
{
	ActionTarget = NewActionTarget;
}

void UBattleComponent::BattleAction_Implementation()
{
}

void UBattleComponent::Attack_Implementation()
{
}

void UBattleComponent::MeleeAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("MeleeTarget  %s"), *ActionTarget->GetName());
	checkf(ActionTarget != nullptr, TEXT("ActionTarget doesn't exist"));
	SetCharacterRotation();
	Character->SetActorRotation(CharacterRot, ETeleportType::None);
	//Character->SetDestination(ActionTarget->GetActorLocation(), 0.0, 5.0);

}

void UBattleComponent::RangetAttack()
{
	
	//GetOwner()->SetActorRotation(, ETeleportType::None);
	CalculateDamage();
	//SpawnActor(); have to spawn projectileclass actor

}

void UBattleComponent::WeakHeal()
{
}

void UBattleComponent::BackToBattlePos()
{
	
	GoBack = false;
	IsTurnEnd = true;
	GetOwner()->SetActorRotation(BattlePosition.GetRotation(), ETeleportType::None);
	// settimerby function name have to be here
	// have to call function that put unit back to array

}

int32 UBattleComponent::CalculateDamage()
{
	
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	int32 Damage = StatusComponent->GetCharacterStatus().AttackPower + 0;// have to put LevelDamage at place of 0
	return 0.0f;
}

void UBattleComponent::DoAction(FName NewActionName)
{
	
	if(NewActionName == "NormalAttack")
	{
		UE_LOG(LogTemp, Warning, TEXT("ActionTarget  %s"), *ActionTarget->GetName());
		MeleeAttack();
	}
	else if(NewActionName == "WeakHeal")
	{
		WeakHeal();
	}
	else if (NewActionName == "RangeAttack")
	{
		RangetAttack();
	}
}

void UBattleComponent::ReachToDestination()
{
}



void UBattleComponent::SetCharacterRotation()
{
	
	IsTurnEnd = false;
	checkf(ActionTarget != nullptr, TEXT("ActionTarget doesn't exist"));
	CharacterRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), ActionTarget->GetActorLocation());
	
}
