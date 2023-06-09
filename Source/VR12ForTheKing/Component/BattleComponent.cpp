// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/BattleComponent.h"
#include "../Character/MyCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "StatusComponent.h"

#include "Net/UnrealNetwork.h"
//#include "../MyGameModeBase.h"
#include "BattleManagerComponent.h"
#include "../Event/TileEventManager.h"
#include "../Widget/ActionWidget.h"
#include "../Widget/BattleWidget.h"
#include "../Widget/DamageText.h"
#include "Components/WidgetComponent.h"

#include "../GameState/MoveBoardGameState.h"
#include "../PlayerController/MoveBoardPlayerController.h"
// Sets default values for this component's properties
UBattleComponent::UBattleComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	SetIsReplicated(true);
	// ...
}


// Called when the game starts
void UBattleComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UBattleComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UBattleComponent, ActionTarget);
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
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 600, FColor::Turquoise, FString::Printf(TEXT("TargetCamera : %s"), *TargetCamera->GetName()));
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
	// From : 
	/*AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* NewBattleManagerComponent =
		Cast<UBattleManagerComponent>(GameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));
	NewBattleManagerComponent->MoveToNextUnitTurn();*/

	AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(GameState);
	GameState->MoveToNextTurn();
}


void UBattleComponent::BattleAction_Implementation()
{
}

void UBattleComponent::Attack_Implementation()
{
}

void UBattleComponent::EndAttack()
{
	//go back to BaseTransform position after give damage
	FQuat GoBackQuat(0.0f, 0.0f, 1.0f, 0.0f);// use to change character rotation
	GetOwner()->SetActorRotation(BaseTransform.GetRotation() * GoBackQuat, ETeleportType::None);
	GetOwner<AMyCharacter>()->SetDestination(BaseTransform.GetLocation(), 0.0, 10.0); // fix shaking problem by setting Destionation Radius larger
}


void UBattleComponent::ChanceCoinCheck()
{	
	/*UTileEventManager* TileEventMangaer = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(TileEventMangaer);

	UDataTable* ActionDataTable = TileEventMangaer->GetActionDataTable();
	checkf(ActionDataTable != nullptr, TEXT("ActionDataTable is not valid"));
	FAction* TargetAction = ActionDataTable->FindRow<FAction>(TargetActionName, 0);
	checkf(TargetAction != nullptr, TEXT("Cannot find NewAction"));*/

	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("UBattleComponent::ChanceCoinCheck")));

	AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(GameState);
	FAction* TargetAction = GameState->GetBattleAction(TargetActionName);
	check(TargetAction);

	ChanceArray.Empty();

	for (int i = 0; i < TargetAction->CheckCount; ++i)
	{
		int32 CoinCheck = FMath::RandRange(1, 100);

		if (1 <= CoinCheck && CoinCheck <= TargetAction->CheckPercent)
		{
			ChanceArray.Add(true);

		}
		else
		{
			ChanceArray.Add(false);
		}
	}
	// for last collapsed slot to show all the chancecoin
	ChanceArray.Add(false);

	CalculateDamage(TargetAction->CheckCount);

	if (FactionType == EFactionType::Player)
	{
		for (auto Iter = GetWorld()->GetPlayerControllerIterator(); Iter; ++Iter)
		{
			AMoveBoardPlayerController* PC = Cast<AMoveBoardPlayerController>(Iter->Get());
			check(PC);
			PC->StartUpdateChanceSlot(TargetAction->CheckCount, TargetAction->StatType, ChanceArray);
		}
	}

	//
	//AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	//UBattleManagerComponent* NewBattleManagerComponent =
	//Cast<UBattleManagerComponent>(GameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));
	//UBattleWidget* NewBattleWidget = Cast<UBattleWidget>(NewBattleManagerComponent->GetBattleWidget());

	//if (FactionType == EFactionType::Player)
	//{
	//	NewBattleWidget->StartUpdateChanceSlot(ChanceArray);
	//}
}

bool UBattleComponent::MeleeAttack()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Purple, FString::Printf(TEXT("%s MeleeAttack"), *GetOwner()->GetName()));
	/*UE_LOG(LogTemp, Warning, TEXT("MeleeAttack"));
	if (ActionTarget == nullptr || !IsValidChecked(ActionTarget))
	{
		UE_LOG(LogTemp, Warning, TEXT("Target is not set"));
		return false;
	}*/
	
	//BattleWidget->StartUpdateChanceSlot(ChanceArray);
	// Damage;

	UE_LOG(LogTemp, Warning, TEXT("ActionTargetName %s"), *ActionTarget->GetName());
	bGoToTarget = true;

	AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());

	FVector Direction = NewCharacter->GetActorLocation() - ActionTarget->GetActorLocation();
	Direction.Normalize();
	NewCharacter->SetDestination(ActionTarget->GetActorLocation() + Direction * 200.0f, 0.0, 10.0);

	return true;
}

void UBattleComponent::RangetAttack()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Purple, FString::Printf(TEXT("%s RangetAttack"), *GetOwner()->GetName()));
	SetCharacterRotation();
	GetOwner()->SetActorRotation(CharacterRot, ETeleportType::None);
	GiveDamage();
	EndTurn();
	//SpawnActor(); have to spawn projectileclass actor

}

void UBattleComponent::WeakHeal()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 30, FColor::Purple, FString::Printf(TEXT("%s WeakHeal"), *GetOwner()->GetName()));
	EndTurn();
}

void UBattleComponent::Resurrection(AMyCharacter* TargetCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("Resurrection"));
	/*AMyGameModeBase* GameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
	UBattleManagerComponent* NewBattleManagerComponent =
		Cast<UBattleManagerComponent>(GameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));

	NewBattleManagerComponent->ResurrectCharacter(TargetCharacter);*/

	EndTurn();
}

void UBattleComponent::BackToBattlePos()
{
	bIsTurnEnd = true;
	FQuat GoBackQuat(0.0f, 0.0f, 1.0f, 0.0f);// use to change character rotation
	GetOwner()->SetActorRotation(BaseTransform.GetRotation(), ETeleportType::None);


}

void UBattleComponent::CalculateDamage(int32 TargetCheckCount)
{
	int32 SuccessCount = 0;
	for (int i = 0; i < ChanceArray.Num() - 1; ++i) // Check Fail Count; delet ChanceArrayNum And Use ChanceArray.Num()
	{
		if (ChanceArray[i]==true)  // Check Whether index i of ChanceArray is Fail or not
		{
			++SuccessCount;
		}

	}


	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->FindComponentByClass(UStatusComponent::StaticClass()));
	 Damage = ((StatusComponent->GetAttackPower())/ TargetCheckCount)*SuccessCount;  
	 UE_LOG(LogTemp, Warning, TEXT("Default: %d, CheckCountedDamage: %d"), StatusComponent->GetAttackPower(), Damage);
}

void UBattleComponent::GiveDamage()
{
	if (ActionTarget != nullptr)
	{
		UBattleComponent* BattleComponent = Cast<UBattleComponent>(ActionTarget->FindComponentByClass(UBattleComponent::StaticClass()));
		checkf(BattleComponent != nullptr, TEXT("TargetCharacter has not BattleComponent"));

		BattleComponent->ReceiveDamage(Damage);
	}


}

void UBattleComponent::ReceiveDamage(int NewDamage)
{
	UStatusComponent* StatusComponent = Cast<UStatusComponent>(GetOwner()->FindComponentByClass(UStatusComponent::StaticClass()));

	StatusComponent->SetCurrentHP(StatusComponent->GetCurrentHP() - NewDamage);
	//int32 DamagedHP = TargetStatusComponent->GetCurrentHP() - CalculateDamage();
	//FString DamagedCharacterName = ActionTarget->GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s CurrentHP : %d"), *GetOwner()->GetName(), StatusComponent->GetCurrentHP());
	//TargetStatusComponent->SetCurrentHP(DamagedHP);
	//CreateDamageTextWidget();
	
	if (StatusComponent->IsDead())
	{
		/* From :
		AMyGameModeBase* NewGameModeBase = Cast<AMyGameModeBase>(GetWorld()->GetAuthGameMode());
		UBattleManagerComponent* NewBattleManagerComponent = Cast<UBattleManagerComponent>(NewGameModeBase->FindComponentByClass(UBattleManagerComponent::StaticClass()));
		AMyCharacter* DeadCharacter = Cast<AMyCharacter>(this->GetOwner());
		NewBattleManagerComponent->RemoveDeadUnitFromArray(DeadCharacter);*/

		AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
		check(GameState);
		GameState->RemoveDeadUnitFromArray(this->GetOwner<AMyCharacter>());
		
		// Todo : Play Animation And Destroy at end of animation
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



void UBattleComponent::DoAction_Implementation(FName ActionName, AMyCharacter* DeadPlayer)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Purple, FString::Printf(TEXT("UBattleComponent::DoAction")));
	if (this->FactionType == EFactionType::Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("EnemyAction %s"), *TargetActionName.ToString());
		int32 ActionNum = FMath::RandRange(0, ActionArray.Num() - 1);
		TargetActionName = ActionArray[ActionNum];
		ChanceCoinCheck();
		DoActionWork();
	}
	else if (this->FactionType == EFactionType::Player)
	{
		TargetActionName = ActionName;

		if (TargetActionName == "Resurrection")
		{
			Resurrection(DeadPlayer);
		}
		else
		{
			ChanceCoinCheck();
		}
	}
}

void UBattleComponent::DoActionWork()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 10, FColor::Cyan, FString::Printf(TEXT("UBattleComponent::DoActionWork, %s"), *TargetActionName.ToString()));

	if (FactionType == EFactionType::Player)
	{
		ActionTarget = GetWorld()->GetGameState<AMoveBoardGameState>()->GetPlayerController(GetOwner<AMyCharacter>()->GetControllerIndex())->GetActionTarget();
	}

	if (TargetActionName == "NormalAttack")
	{
		MeleeAttack();
	}
	else if (TargetActionName == "WeakHeal")
	{
		WeakHeal();
	}
	else if (TargetActionName == "RangeAttack")
	{
		RangetAttack();
	}
}

void UBattleComponent::ReachToDestination()
{
	//UE_LOG(LogTemp, Warning, TEXT("ReachToDestination"));
	if (bGoToTarget)
	{
		AMyCharacter* NewCharacter = Cast<AMyCharacter>(GetOwner());
		bGoToTarget = false;

		//give damage to actiontarget
		if (TargetActionName == "NormalAttack")
		{
			NewCharacter->PlayAnimation(FName("Attack_Sword"));
		}
	}
	else
	{
		// Return To BaseTransform
		BackToBattlePos();

		EndTurn();
	}
}

void UBattleComponent::CreateDamageTextWidget()
{
	UWidgetComponent* WidgetComponent = Cast<UWidgetComponent>(this->GetOwner()->FindComponentByClass(UWidgetComponent::StaticClass()));

	check(DamageTextClass != nullptr);
	DamageText = CreateWidget<UDamageText>(GetWorld()->GetFirstPlayerController(), DamageTextClass);
	check(DamageText != nullptr);
	DamageText->AddToPlayerScreen(0);
	DamageText->SetVisibility(ESlateVisibility::Visible);
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
