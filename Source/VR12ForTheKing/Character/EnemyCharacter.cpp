// Fill out your copyright notice in the Description page of Project Settings.


#include "../Character/EnemyCharacter.h"
#include "../Component/BattleComponent.h"

AEnemyCharacter::AEnemyCharacter()
{
	BattleComponent->SetFactionType(EFactionType::Enemy);
}