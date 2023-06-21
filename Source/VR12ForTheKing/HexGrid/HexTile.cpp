// Fill out your copyright notice in the Description page of Project Settings.


#include "../HexGrid/HexTile.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "Kismet/GamePlayStatics.h"

//#include "../MyGameModeBase.h"
#include "../Event/EventActor.h"
#include "../Event/TileEventManager.h"
#include "../PlayerController/MoveBoardPlayerController.h"

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

void AHexTile::NotifyActorBeginCursorOver()
{
	Super::NotifyActorBeginCursorOver();
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("AHexTile::NotifyActorBeginCursorOver")));
	GetWorld()->GetFirstPlayerController<AMoveBoardPlayerController>()->SetEndTile(this);
}

// Called every frame
void AHexTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHexTile::SetIsPath_Implementation(bool bNewIsPath, int NewDistance)
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

bool AHexTile::GetIsSearched()
{
	return bIsSearched;
}

void AHexTile::Search()
{
	if (bIsSearched) return;
	bIsSearched = true;

	// Todo : If this tile already has event, invoke the event
}

bool AHexTile::GetIsPassable() const
{
	return bIsPassable;
}

void AHexTile::SetIsPassable(bool bNewIsPassable)
{
	bIsPassable = bNewIsPassable;
}

void AHexTile::ArriveToTile(AMyCharacter* NewArrival)
{
	checkf(NewArrival != nullptr, TEXT("AHexTile::ArriveToTile : NewArrival is nullptr"));
	InTileCharacterArray.Add(NewArrival);

	Search();

	// Todo : Change In Tile Character Location
}

void AHexTile::LeaveFromTile(AMyCharacter* NewLeaver)
{
	checkf(NewLeaver != nullptr, TEXT("AHexTile::LeaveFromTile : NewLeaver is nullptr"));
	int32 Index = InTileCharacterArray.Find(NewLeaver);
	checkf(Index >= 0, TEXT("AHexTile::LeaveFromTile : Index is invalid"));
	InTileCharacterArray.RemoveAt(Index);

	// Todo : Change In Tile Character Location
}

const TArray<AMyCharacter*>& AHexTile::GetInTileCharacterArray() const
{
	return InTileCharacterArray;
}

int32 AHexTile::GetInTileCharacterArrayLength() const
{
	return InTileCharacterArray.Num();
}

AEventActor* AHexTile::GetTileEvent() const
{
	return EventActor;
}

void AHexTile::SpawnEvent(AEventActor* NewEventActor)
{
	Search();
	EventActor = NewEventActor;
}

bool AHexTile::CheckCanSpawnEvent() const
{
	return !(bIsSearched || EventActor != nullptr || InTileCharacterArray.Num() > 0);
}
