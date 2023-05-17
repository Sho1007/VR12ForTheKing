// Fill out your copyright notice in the Description page of Project Settings.


#include "../Battle/BattleMap.h"

// Sets default values
ABattleMap::ABattleMap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PlayerSpawnPosition.Init(nullptr, 3);
	EnemySpawnPosition.Init(nullptr, 3);
}

// Called when the game starts or when spawned
void ABattleMap::BeginPlay()
{
	Super::BeginPlay();
}