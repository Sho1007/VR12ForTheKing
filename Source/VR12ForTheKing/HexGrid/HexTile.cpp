// Fill out your copyright notice in the Description page of Project Settings.


#include "../HexGrid/HexTile.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"

// Sets default values
AHexTile::AHexTile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponet"));
	SetRootComponent(StaticMeshComponent);

	TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>(TEXT("TextRednerComponent"));
	TextRenderComponent->SetupAttachment(RootComponent);
}

void AHexTile::SetParentTile(AHexTile* NewParentTile)
{
	ParentTile = NewParentTile;
}

void AHexTile::SetPos(FIntPoint NewPos)
{
	Pos = NewPos;
	TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%d, %d"), Pos.Y, Pos.X)));
}

// Called when the game starts or when spawned
void AHexTile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AHexTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHexTile::SetIsPath(bool bNewIsPath, int NewDistance)
{
	TextRenderComponent->SetVisibility(bNewIsPath);
	StaticMeshComponent->SetRenderCustomDepth(bNewIsPath);
	if (bNewIsPath)
	{
		TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%d"), NewDistance)));
	}
}

void AHexTile::ClickTile()
{
	StaticMeshComponent->SetRenderCustomDepth(true);
}

void AHexTile::UnClickTile()
{
	StaticMeshComponent->SetRenderCustomDepth(false);
}

