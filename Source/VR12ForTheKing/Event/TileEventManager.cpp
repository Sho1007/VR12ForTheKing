// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventManager.h"

#include "Engine/DataTable.h"
#include "../HexGrid/HexTile.h"
#include "TileEventMeshCapturor.h"

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

	check(TileEventMeshCapturorClass != nullptr);
	TileEventMeshCapturor = GetWorld()->SpawnActor<ATileEventMeshCapturor>(TileEventMeshCapturorClass, FVector(0,0,0), FRotator(0,0,0));
	check(TileEventMeshCapturor != nullptr);
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

const float ATileEventManager::GetEventOccurChance() const
{
	return EventOccurChance;
}

AEventActor* ATileEventManager::SetTileEvent(AHexTile* NewHexTile)
{
	CurrentTileEvent = NewHexTile->GetTileEvent();

	if (CurrentTileEvent != nullptr)
	{
		TileEventMeshCapturor->SetFocusTarget(CurrentTileEvent);
	}

	return CurrentTileEvent;
}

AEventActor* ATileEventManager::GetTileEvent() const
{
	return CurrentTileEvent;
}

