// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventManager.h"

#include "Engine/DataTable.h"

// Sets default values
ATileEventManager::ATileEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ATileEventManager::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(EventDataTable != nullptr, TEXT("ATileEventManager::BeginPlay : EventDataTable is nullptr"));
}

// Called every frame
void ATileEventManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UDataTable* ATileEventManager::GetDataTable()
{
	return EventDataTable;
}

