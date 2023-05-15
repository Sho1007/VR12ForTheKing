// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/EventActor.h"

#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"
#include "TileEventMesh.h"

// Sets default values
AEventActor::AEventActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollisionComponent);
}

// Called when the game starts or when spawned
void AEventActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEventActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEventActor::SetEventInfo(const FEventInfo& NewEventInfo)
{
	EventInfo = NewEventInfo;
	if (EventInfo.TileEventMeshClass != nullptr)
	{
		TileEventMesh = GetWorld()->SpawnActor<ATileEventMesh>(EventInfo.TileEventMeshClass, GetActorLocation(), GetActorRotation());
		checkf(TileEventMesh, TEXT("TileEventMesh Actor is not spawned"));
	}
}

const FText AEventActor::GetEventName() const
{
	return EventInfo.EventName;
}

const FText AEventActor::GetDiscription1() const
{
	return EventInfo.Discription1;
}

const EEventType AEventActor::GetEventType() const
{
	return EventInfo.EventType;
}

const FEventInfo& AEventActor::GetEventInfo() const
{
	return EventInfo;
}

ATileEventMesh* AEventActor::GetTileEventMesh() const
{
	return TileEventMesh;
}
