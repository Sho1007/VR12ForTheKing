// Fill out your copyright notice in the Description page of Project Settings.


#include "../Battle/BattleCharacterSpawnPosition.h"

// Sets default values
ABattleCharacterSpawnPosition::ABattleCharacterSpawnPosition()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ABattleCharacterSpawnPosition::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABattleCharacterSpawnPosition::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

 AActor* ABattleCharacterSpawnPosition::GetCameraPosition() const
{
	return CameraPosition;
}

