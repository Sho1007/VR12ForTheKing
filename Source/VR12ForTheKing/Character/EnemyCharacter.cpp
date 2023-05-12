// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/EnemyCharacter.h"
#include "../Component/BattleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
}

void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	checkf(BattleComponent != nullptr, TEXT("BattleComponent is not valid"));
	if (BattleComponent)
	{
		BattleComponent->SetFactionType(EFactionType::Enemy);
	}	
}
