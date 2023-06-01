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

void UBattleComponent::SetBaseTransform(FTransform NewBaseTransform)
{
	BaseTransform = NewBaseTransform;
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

bool UBattleComponent::MeleeAttack()
{
	/*GoBack = true;
	if (ActionTarget == nullptr)
	{
		return false;
	}
	UE_LOG(LogTemp, Warning, TEXT("MeleeTarget  %s"), *ActionTarget->GetName());
	SetCharacterRotation();
	AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
	NewCharacter->SetDestination(ActionTarget->GetActorLocation(), 0.0, 5.0);
	*/

	bGoToTarget = true;
	AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
	NewCharacter->SetDestination(ActionTarget->GetActorLocation(), 0.0, 5.0);
	
	return true;
}

void UBattleComponent::RangetAttack()
{
	SetCharacterRotation();
	GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
	CalculateDamage();
	//SpawnActor(); have to spawn projectileclass actor

}

void UBattleComponent::WeakHeal()
{
}

void UBattleComponent::BackToBattlePos()
{
	bIsTurnEnd = true;
	FQuat GoBackQuat(0.0f, 0.0f, 1.0f, 0.0f);// use to change character rotation
	GetOwner()->SetActorRotation(BaseTransform.GetRotation(), ETeleportType::None);


}

int32 UBattleComponent::CalculateDamage()
{
	
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->GetComponentByClass(UStatusComponent::StaticClass()));
	int32 Damage = StatusComponent->GetAttackPower() + 0;// have to put LevelDamage at place of 0
	return 0.0f;
}

void UBattleComponent::DoAction(FName NewActionName)
{
	
	if(NewActionName == "NormalAttack")
	{
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
	UE_LOG(LogTemp, Warning, TEXT("ReachToDestination"));
	if (bGoToTarget)
	{
		// Reached to Target
		// Todo : Play Animation
		// Todo : Apply Damage
		// DoAttack();
		bGoToTarget = false;
		AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
		FQuat GoBackQuat(0.0f, 0.0f, 1.0f, 0.0f);// use to change character rotation
		GetOwner()->SetActorRotation(BaseTransform.GetRotation()* GoBackQuat, ETeleportType::None);
		NewCharacter->SetDestination(BaseTransform.GetLocation(), 0.0, 1.0);
	}
	else
	{
		// Return To BaseTransform
		BackToBattlePos();

	}
}





void UBattleComponent::SetCharacterRotation()
{
	UE_LOG(LogTemp, Warning, TEXT("Run SetCharacterRotation"));
	bIsTurnEnd = false;
	checkf(ActionTarget != nullptr, TEXT("ActionTarget doesn't exist"));
	CharacterRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), ActionTarget->GetActorLocation());
	FString CharacterRotString = CharacterRot.ToString();
	UE_LOG(LogTemp, Warning, TEXT("CharacterRotation %s"), *CharacterRotString);
	GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
}
