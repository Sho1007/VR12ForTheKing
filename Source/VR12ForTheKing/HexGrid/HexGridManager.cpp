// Fill out your copyright notice in the Description page of Project Settings.


#include "../HexGrid/HexGridManager.h"

#include "../HexGrid/HexTile.h"

// Sets default values
AHexGridManager::AHexGridManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AHexGridManager::BeginPlay()
{
	Super::BeginPlay();
	CreateGrid();
}

// Called every frame
void AHexGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AHexGridManager::CreateGrid()
{
	FVector SpawnLocation;
	FRotator SpawnRotation(0, 0, 0);
	for (int i = 0; i < Height; ++i)
	{
		SpawnLocation.X = i % 2 == 0 ? 0 : XStartOffset;
		HexGrid.Add(FTileRow());
		for (int j = 0; j < Width; ++j)
		{
			AHexTile* HexTile = GetWorld()->SpawnActor<AHexTile>(HexTileClass, SpawnLocation, SpawnRotation);
			HexGrid[i].TileArray.Add(HexTile);
			SpawnLocation.X += XOffset;
		}
		SpawnLocation.Y += YOffset;
	}
}

