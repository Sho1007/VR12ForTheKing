// Fill out your copyright notice in the Description page of Project Settings.


#include "../HexGrid/HexTile.h"

#include "Components/StaticMeshComponent.h"
#include "Components/TextRenderComponent.h"
#include "../Event/EventActor.h"
#include "Kismet/GamePlayStatics.h"
#include "../MyGameModeBase.h"
#include "../Event/TileEventManager.h"

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

AEventActor* AHexTile::GetTileEvent() const
{
	return EventActor;
}

void AHexTile::SpawnEvent()
{
	// Random Spawn Event But Now Static Enemy Event
	//EventActor = GetWorld()->SpawnActor<AEventActor>();

	AMyGameModeBase* GameMode = Cast<AMyGameModeBase>(UGameplayStatics::GetGameMode(this));
	checkf(GameMode != nullptr, TEXT("AHexTile::SpawnEvent : GameMode is not valid"));
	UDataTable* EventDataTable = GameMode->GetTileEventManager()->GetDataTable();
	TArray<FName> List = EventDataTable->GetRowNames();
	FName RandomName = List[FMath::RandRange(0, List.Num() - 1)];
	FEventInfo* EventInfo = EventDataTable->FindRow<FEventInfo>(RandomName, FString(""));

	EventActor = GetWorld()->SpawnActor<AEventActor>(EventInfo->EventActorClass, GetActorLocation(), GetActorRotation());
	checkf(EventActor != nullptr, TEXT("AHexTile::SpawnEvent : EventActor is not spawned"));
	EventActor->SetEventInfo(*EventInfo);
}