// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/EventActor.h"

#include "Components/BoxComponent.h"
#include "Components/ChildActorComponent.h"

// Sets default values
AEventActor::AEventActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BoxCollisionComponent = CreateDefaultSubobject<UBoxComponent>("BoxCollision");
	SetRootComponent(BoxCollisionComponent);

	EventMeshComponent = CreateDefaultSubobject<UChildActorComponent>("EventMesh");
	EventMeshComponent->SetupAttachment(RootComponent);
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

const FText AEventActor::GetEventName() const
{
	return EventName;
}

const FText AEventActor::GetDiscription1() const
{
	return Discription1;
}

const EEventType AEventActor::GetEventType() const
{
	return EventType;
}