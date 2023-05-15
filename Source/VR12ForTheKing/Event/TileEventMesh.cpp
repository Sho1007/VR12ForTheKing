// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventMesh.h"

#include "Components/ArrowComponent.h"

// Sets default values
ATileEventMesh::ATileEventMesh()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	
	SetRootComponent(CreateDefaultSubobject<USceneComponent>("RootComponent"));

	CapturePosition = CreateDefaultSubobject<UArrowComponent>("CapturorPosition");
	CapturePosition->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ATileEventMesh::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileEventMesh::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

const FTransform& ATileEventMesh::GetCapturePosition() const
{
	return CapturePosition->GetComponentTransform();
}

