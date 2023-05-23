// Fill out your copyright notice in the Description page of Project Settings.


#include "../Battle/BattleMap.h"

// Sets default values
ABattleMap::ABattleMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void ABattleMap::BeginPlay()
{
	Super::BeginPlay();
}

const TArray<AActor*>& ABattleMap::GetEnemySpawnPosition() const
{
	return BattleSceneInfoArray[CurrentSceneIndex].EnemySpawnPosition;
}

const TArray<AActor*>& ABattleMap::GetPlayerSpawnPosition() const
{
	return BattleSceneInfoArray[CurrentSceneIndex].PlayerSpawnPosition;
}

const AActor* ABattleMap::GetPlayerSideCamera() const
{
	return BattleSceneInfoArray[CurrentSceneIndex].PlayerSideCamera;
}

const AActor* ABattleMap::GetEnemySideCamera() const
{
	return BattleSceneInfoArray[CurrentSceneIndex].EnemySideCamera;
}

const AActor* ABattleMap::GetNeutralSideCamera() const
{
	return BattleSceneInfoArray[CurrentSceneIndex].NeutralSideCamera;
}

const AActor* ABattleMap::GetNextNeutralSideCamera() const
{
	if (IsLastScene()) return nullptr;
	return BattleSceneInfoArray[CurrentSceneIndex + 1].NeutralSideCamera;
}

const int32 ABattleMap::GetLastSceneIndex() const
{
	return BattleSceneInfoArray.Num() - 1;
}

const int32 ABattleMap::GetCurrentSceneIndex() const
{
	return CurrentSceneIndex;
}

const bool ABattleMap::IsLastScene() const
{
	return CurrentSceneIndex == BattleSceneInfoArray.Num() - 1;
}

const bool ABattleMap::MoveNextSceneIndex()
{
	if (IsLastScene()) return false;
	CurrentSceneIndex++;
	return true;
}
