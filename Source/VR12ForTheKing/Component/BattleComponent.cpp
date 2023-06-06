// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleComponent.h"
#include "../Character/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "StatusComponent.h"
#include "../MyGameModeBase.h"
#include "BattleManagerComponent.h"

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

AMyCharacter* UBattleComponent::GetActionTarget()
{
	return ActionTarget;
}

void UBattleComponent::EndTurn()
{
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* NewBattleManagerComponent =
		Cast<UBattleManagerComponent>(GameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));
	NewBattleManagerComponent->MoveToNextUnitTurn();

}

void UBattleComponent::RandomEnemyAction()
{
	int32 ActionNum = FMath::RandRange(0, ActionArray.Num() - 1);
	FString ActionName = ActionArray[ActionNum].ToString();
	UE_LOG(LogTemp, Warning, TEXT("EnemyAction %s"), *ActionName);

	DoAction(ActionArray[ActionNum]);
	
}

void UBattleComponent::BattleAction_Implementation()
{
}

void UBattleComponent::Attack_Implementation()
{
}

bool UBattleComponent::MeleeAttack()
{
	
	if (ActionTarget == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is not set"));
		return false;

	}
		

	bGoToTarget = true;
	AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
	NewCharacter->SetDestination(ActionTarget->GetActorLocation(), 0.0, 5.0);
	
	return true;
}

void UBattleComponent::RangetAttack()
{
	SetCharacterRotation();
	GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
	GiveDamage();
	EndTurn();
	//SpawnActor(); have to spawn projectileclass actor

}

void UBattleComponent::WeakHeal()
{
	EndTurn();
}

void UBattleComponent::BackToBattlePos()
{
	bIsTurnEnd = true;
	FQuat GoBackQuat(0.0f, 0.0f, 1.0f, 0.0f);// use to change character rotation
	GetOwner()->SetActorRotation(BaseTransform.GetRotation(), ETeleportType::None);


}

int32 UBattleComponent::CalculateDamage()
{
	
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->FindComponentByClass(UStatusComponent::StaticClass()));
	int32 Damage = StatusComponent->GetAttackPower() + 0;// have to put LevelDamage at place of 0
	return Damage;
}

void UBattleComponent::GiveDamage()
{
	CalculateDamage();
	UStatusComponent* TargetStatusComponent = Cast<UStatusComponent>(ActionTarget->FindComponentByClass(UStatusComponent::StaticClass()));
	int32 DamagedHP = TargetStatusComponent->GetCurrentHP() - CalculateDamage();
	FString DamagedCharacterName = ActionTarget->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s Current Health %d  Damge %d DamagedHP %d"), *DamagedCharacterName, TargetStatusComponent->GetCurrentHP(), CalculateDamage(), DamagedHP);
	TargetStatusComponent->SetCurrentHP(DamagedHP);
	
		AMyGameModeBase* NewGameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
		UBattleManagerComponent* NewBattleManagerComponent = Cast<UBattleManagerComponent>(NewGameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));

		NewBattleManagerComponent->RemoveDeadUnitFromArray();
		
	
}


bool UBattleComponent::IsDead()
{
	
		UStatusComponent* TargetStatusComponent = Cast<UStatusComponent>(GetOwner()->FindComponentByClass(UStatusComponent::StaticClass()));
		int32 TargetCurrentHP = TargetStatusComponent->GetCurrentHP();

		if (TargetCurrentHP <= 0)
		{
			TargetCurrentHP = 0;
			FString DeadCharacterName = GetOwner()->GetName();
			UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *DeadCharacterName);

			return true;
		}
		else
		{
			return false;
		}
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
	//UE_LOG(LogTemp, Warning, TEXT("ReachToDestination"));
	if (bGoToTarget)
	{
		
		bGoToTarget = false;

		//give damage to actiontarget
		GiveDamage();
		
		//go back to BaseTransform position after give damage

		AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
		FQuat GoBackQuat(0.0f, 0.0f, 1.0f, 0.0f);// use to change character rotation
		GetOwner()->SetActorRotation(BaseTransform.GetRotation()* GoBackQuat, ETeleportType::None);
		NewCharacter->SetDestination(BaseTransform.GetLocation(), 0.0, 1.0);
	}
	else
	{
		// Return To BaseTransform
		BackToBattlePos();
		
		EndTurn();
	}
}





void UBattleComponent::SetCharacterRotation()
{
	//UE_LOG(LogTemp, Warning, TEXT("Run SetCharacterRotation"));
	bIsTurnEnd = false;
	checkf(ActionTarget != nullptr, TEXT("ActionTarget doesn't exist"));
	CharacterRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), ActionTarget->GetActorLocation());
	FString CharacterRotString = CharacterRot.ToString();
	//UE_LOG(LogTemp, Warning, TEXT("CharacterRotation %s"), *CharacterRotString);
	GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
}
