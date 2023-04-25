// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameModeBase.h"

#include "HexGrid/HexGridManager.h"

void AMyGameModeBase::BeginPlay()
{
	HexGridManager = GetWorld()->SpawnActor<AHexGridManager>();
	if (HexGridManager)
	{
		//HexGridManager->Initialize();
	}
}
