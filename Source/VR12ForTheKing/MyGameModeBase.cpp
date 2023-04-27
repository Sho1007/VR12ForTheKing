// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "HexGrid/HexGridManager.h"
#include "HexGrid/HexTile.h"
#include "Character/MyCharacter.h"
#include "Kismet/GameplayStatics.h"

void AMyGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	PrimaryActorTick.bCanEverTick = false;

	TArray<AActor*> OutActors;
	UGameplayStatics::GetAllActorsOfClass(this, HexGridManagerClass, OutActors);
	if (OutActors.Num() > 0)
	{
		HexGridManager = CastChecked<AHexGridManager>(OutActors[0]);
	}
	CreateHexGrid();
	CreatePlayer();
}

void AMyGameModeBase::SetStartTile(AHexTile* NewStartTile)
{
	StartTile = NewStartTile;
}

void AMyGameModeBase::SetEndTile(AHexTile* NewEndTile)
{
	EndTile = NewEndTile;
	FindPath();
}

void AMyGameModeBase::FindPath()
{
	
}

void AMyGameModeBase::CreateHexGrid()
{
	if (HexGridManager)
	{
		HexGridManager->CreateGrid();
	}
}

void AMyGameModeBase::CreatePlayer()
{
	if (CharacterClass)
	{
		FVector SpawnLocation(0, 0, 0);
		for (int i = 0; i < 3; ++i)
		{
			CharacterArray.Add(GetWorld()->SpawnActor<AMyCharacter>(CharacterClass, SpawnLocation, FRotator(0, 0, 0)));
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("MyGameModeBase:: CharacterClass is not valid"));
	}
}