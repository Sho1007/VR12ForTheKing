// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventManager.h"

#include "Engine/DataTable.h"
#include "Net/UnrealNetwork.h"

#include "../HexGrid/HexTile.h"
#include "../Event/EventActor.h"
#include "TileEventMeshCapturor.h"
#include "../HexGrid/HexGridManager.h"
#include "../Widget/TileEventWidget.h"
#include "../Component/BattleComponent.h"
#include "../HUD/MoveBoardHUD.h"

// Sets default values
UTileEventManager::UTileEventManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicated(true);
}

// Called when the game starts or when spawned
void UTileEventManager::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(EventDataTable != nullptr, TEXT("ATileEventManager::BeginPlay : EventDataTable is nullptr"));

	check(TileEventMeshCapturorClass != nullptr);
	TileEventMeshCapturor = GetWorld()->SpawnActor<ATileEventMeshCapturor>(TileEventMeshCapturorClass, FVector(0,0,0), FRotator(0,0,0));
	check(TileEventMeshCapturor != nullptr);
}

void UTileEventManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UTileEventManager, CurrentTileEvent);
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

	OnRep_CurrentTileEvent();

	return CurrentTileEvent;
}

AEventActor* UTileEventManager::GetCurrentTileEvent() const
{
	return CurrentTileEvent;
}

FAction* UTileEventManager::FindActionInfo(FName TargetActionRow) const
{
	if (TargetActionRow == FName("None")) return nullptr;
	FAction* ActionInfo = ActionDataTable->FindRow<FAction>(TargetActionRow, FString(""));

	return ActionInfo;
}

void UTileEventManager::OnRep_CurrentTileEvent()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("OnRep_CurrentTileEvent")));
	if (CurrentTileEvent != nullptr)
	{
		TileEventMeshCapturor->SetFocusTarget(CurrentTileEvent);
		AMoveBoardHUD* HUD = GetWorld()->GetFirstPlayerController()->GetHUD<AMoveBoardHUD>();
		check(HUD);
		HUD->InitTileEventWidget(CurrentTileEvent);
	}
}