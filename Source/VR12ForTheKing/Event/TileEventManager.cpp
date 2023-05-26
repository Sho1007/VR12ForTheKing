// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventManager.h"

#include "Engine/DataTable.h"
#include "../HexGrid/HexTile.h"
#include "../Event/EventActor.h"
#include "TileEventMeshCapturor.h"
#include "../HexGrid/HexGridManager.h"
#include "../Widget/TileEventWidget.h"

// Sets default values
UTileEventManager::UTileEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void UTileEventManager::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(EventDataTable != nullptr, TEXT("ATileEventManager::BeginPlay : EventDataTable is nullptr"));

	check(TileEventMeshCapturorClass != nullptr);
	TileEventMeshCapturor = GetWorld()->SpawnActor<ATileEventMeshCapturor>(TileEventMeshCapturorClass, FVector(0,0,0), FRotator(0,0,0));
	check(TileEventMeshCapturor != nullptr);

	CreateTileEventWidget();
}
 
void UTileEventManager::SpawnEvent(AHexTile* CenterTile)
{
	UHexGridManager* HexGridManager = Cast<UHexGridManager>(GetOwner()->GetComponentByClass(UHexGridManager::StaticClass()));
	check(HexGridManager != nullptr);
	TArray<AHexTile*> NeighborTileArray;
	HexGridManager->FindNeighborTiles(NeighborTileArray, CenterTile, 2);

	for (AHexTile* HexTile : NeighborTileArray)
	{
		if (FMath::RandRange(0.0, 1.0) <= EventOccurChance)
		{
			if (!HexTile->CheckCanSpawnEvent()) continue;

			TArray<FName> List = EventDataTable->GetRowNames();
			FName RandomName = List[FMath::RandRange(0, List.Num() - 1)];
			FEventInfo* EventInfo = EventDataTable->FindRow<FEventInfo>(RandomName, FString(""));

			AEventActor* EventActor = GetWorld()->SpawnActor<AEventActor>(EventInfo->EventActorClass, HexTile->GetActorLocation(), HexTile->GetActorRotation());
			check(EventActor != nullptr);
			EventActor->SetEventInfo(*EventInfo);

			HexTile->SpawnEvent(EventActor);
		}
	}
}

void UTileEventManager::SetFocusTarget(AActor* NewActor)
{
	if (NewActor == CurrentFocusEvent) return;
	if (CurrentFocusEvent)
	{
		// Todo : HideEventInfoWidget();
		CurrentFocusEvent = nullptr;
	}

	AEventActor* NewEventActor = Cast<AEventActor>(NewActor);
	if (NewEventActor)
	{
		CurrentFocusEvent = NewEventActor;
		FVector2D ScreenLocation;
		GetWorld()->GetFirstPlayerController()->ProjectWorldLocationToScreen(CurrentFocusEvent->GetActorLocation(), ScreenLocation);
		// Todo : InitAndShowEventInfoWidget(EventActor, ScreenLocation);
	}
}

UDataTable* UTileEventManager::GetEventDataTable()
{
	return EventDataTable;
}

UDataTable* UTileEventManager::GetActionDataTable()
{
	return ActionDataTable;
}

const float UTileEventManager::GetEventOccurChance() const
{
	return EventOccurChance;
}

AEventActor* UTileEventManager::SetCurrentTileEvent(AHexTile* NewHexTile)
{
	CurrentTileEvent = NewHexTile->GetTileEvent();

	if (CurrentTileEvent != nullptr)
	{
		TileEventMeshCapturor->SetFocusTarget(CurrentTileEvent);
		InitAndShowEventDiscription();
	}

	return CurrentTileEvent;
}

AEventActor* UTileEventManager::GetTileEvent() const
{
	return CurrentTileEvent;
}

void UTileEventManager::HideWidget()
{
	TileEventWidget->HideEventInfoWidget();
	TileEventWidget->HideEventWidget();
}

void UTileEventManager::InitAndShowEventDiscription()
{
	TileEventWidget->InitEventWidget(CurrentTileEvent);
	TileEventWidget->ShowEventWidget();
}

void UTileEventManager::CreateTileEventWidget()
{
	checkf(TileEventWidgetClass != nullptr, TEXT("TileEventWidgetClass is nullptr"));
	TileEventWidget = CreateWidget<UTileEventWidget>(GetWorld()->GetFirstPlayerController(), TileEventWidgetClass);
	checkf(TileEventWidget != nullptr, TEXT("TileEventWidget is not created"));
	TileEventWidget->AddToPlayerScreen(0);
	HideWidget();
}