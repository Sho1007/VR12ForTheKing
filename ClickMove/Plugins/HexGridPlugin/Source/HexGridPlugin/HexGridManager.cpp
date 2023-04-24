// Fill out your copyright notice in the Description page of Project Settings.


#include "HexGridManager.h"
#include "HexTile.h"

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

	FVector SpawnLocation(0, 0, 0);

	for (int i = 0; i < Height; ++i)
	{
		SpawnLocation.X = i % 2 == 0 ? 0.0f : XStartOffset;
		HexGrid.Add(FTileRow());
		for (int j = 0; j < Width; ++j)
		{
			AHexTile* HexTile = GetWorld()->SpawnActor<AHexTile>(HexTileClass, SpawnLocation, FRotator(0,0,0));
			HexGrid[i].TileRowArray.Add(HexTile);
			SpawnLocation.X += XOffset;
		}
		SpawnLocation.Y += YOffset;
	}
}

// Called every frame
void AHexGridManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

