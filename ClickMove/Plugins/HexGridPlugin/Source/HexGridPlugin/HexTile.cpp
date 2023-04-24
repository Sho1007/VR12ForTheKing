// Fill out your copyright notice in the Description page of Project Settings.


#include "HexTile.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AHexTile::AHexTile()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	SetRootComponent(StaticMeshComponent);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> StaticMesh(TEXT("StaticMesh'/HexGridPlugin/Meshes/HexMesh.HexMesh'"));
	if (StaticMesh.Succeeded())
	{
		StaticMeshComponent->SetStaticMesh(StaticMesh.Object);
		UE_LOG(LogTemp, Warning, TEXT("HexTile:: Static Mesh Is Setted Successfully"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("HexTile:: Static Mesh Is Not Valid"));
	}
}
