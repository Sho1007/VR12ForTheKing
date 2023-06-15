// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleComponent.h"
#include "../Character/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "StatusComponent.h"
#include "../MyGameModeBase.h"
#include "BattleManagerComponent.h"
#include "../Widget/ActionWidget.h"
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

void UBattleComponent::SetTargetCamera(AActor* NewTargetCamera)
{
	TargetCamera = NewTargetCamera;

}

AActor* UBattleComponent::GetTargetCamera() const
{
	return TargetCamera;
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

	if (ActionName == "NormalAttack")
	{
		MeleeAttack();
	}
	else if (ActionName == "WeakHeal")
	{
		WeakHeal();
	}
	else if (ActionName == "RangeAttack")
	{
		RangetAttack();
	}

}

void UBattleComponent::BattleAction_Implementation()
{
}

void UBattleComponent::Attack_Implementation()
{
}

bool UBattleComponent::MeleeAttack()
{

	UE_LOG(LogTemp, Warning, TEXT("MeleeAttack"));
	if (ActionTarget == nullptr || !ActionTarget->IsValidLowLevelFast() || ActionTarget->IsPendingKill())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is not set"));
		return false;

	}

	UE_LOG(LogTemp, Warning, TEXT("ActionTargetName %s"), *ActionTarget->GetName());
	bGoToTarget = true;
	AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
	NewCharacter->SetDestination(ActionTarget->GetActorLocation(), 0.0, 5.0);

	return true;
}

void UBattleComponent::RangetAttack()
{
	UE_LOG(LogTemp, Warning, TEXT("RangeAttack"));
	SetCharacterRotation();
	GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
	GiveDamage();
	EndTurn();
	//SpawnActor(); have to spawn projectileclass actor

}

void UBattleComponent::WeakHeal()
{
	if (ActionTarget == nullptr || !ActionTarget->IsValidLowLevelFast() || ActionTarget->IsPendingKill())
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is not set"));
	}
	if (ActionTarget != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("WeakHeal"));
		EndTurn();
	}
}

void UBattleComponent::Resurrection(AMyCharacter* TargetCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Resurrection"));
	AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* NewBattleManagerComponent =
		Cast<UBattleManagerComponent>(GameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));

	NewBattleManagerComponent->ResurrectCharacter(TargetCharacter);

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
	if (ActionTarget != nullptr)
	{
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(ActionTarget->FindComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("TargetCharacter has not BattleComponent"));

		BattleComponent->ReceiveDamage(CalculateDamage());
	}


}

void UBattleComponent::ReceiveDamage(int Damage)
{
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->FindComponentByClass(UStatusComponent::StaticClass()));

	StatusComponent->SetCurrentHP(StatusComponent->GetCurrentHP() - CalculateDamage());
	//int32 DamagedHP = TargetStatusComponent->GetCurrentHP() - CalculateDamage();
	//FString DamagedCharacterName = ActionTarget->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s CurrentHP : %d"), *GetOwner()->GetName(), StatusComponent->GetCurrentHP());
	//TargetStatusComponent->SetCurrentHP(DamagedHP);

	
	if (StatusComponent->IsDead())
	{
		AMyGameModeBase* NewGameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
		UBattleManagerComponent* NewBattleManagerComponent = Cast<UBattleManagerComponent>(NewGameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));
		
		AMyCharacter* DeadCharacter = Cast<AMyCharacter>(this->GetOwner());
		NewBattleManagerComponent->RemoveDeadUnitFromArray(DeadCharacter);

		if (GetFactionType() == EFactionType::Enemy)
		{
			this->GetOwner()->Destroy();
		}
	}
}


bool UBattleComponent::IsDead()
{/*
	UE_LOG(LogTemp, Warning, TEXT("%s is Dead"), *DeadCharacterName);
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
	}*/

	return false;
} 



void UBattleComponent::DoAction(UActionWidget* ActionWidget)
{

	if (ActionWidget->GetActionName() == "NormalAttack")
	{
		MeleeAttack();
	}
	else if (ActionWidget->GetActionName() == "WeakHeal")
	{
		WeakHeal();
	}
	else if (ActionWidget->GetActionName() == "RangeAttack")
	{
		RangetAttack();
	}
	else if (ActionWidget->GetActionName() == "Resurrection")
	{
		Resurrection(ActionWidget->GetDeadPlayer());
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
		GetOwner()->SetActorRotation(BaseTransform.GetRotation() * GoBackQuat, ETeleportType::None);
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

	if (ActionTarget != nullptr)
	{
		CharacterRot = UKismetMathLibrary::FindLookAtRotation(GetOwner()->GetActorLocation(), ActionTarget->GetActorLocation());
		FString CharacterRotString = CharacterRot.ToString();
		//UE_LOG(LogTemp, Warning, TEXT("CharacterRotation %s"), *CharacterRotString);
		GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
	}

}
