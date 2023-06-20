// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventMeshCapturor.h"

#include "Components/SceneCaptureComponent2D.h"
#include "EventActor.h"
#include "TileEventMesh.h"

// Sets default values
ATileEventMeshCapturor::ATileEventMeshCapturor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneCaptureComponent = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent");
}

// Called when the game starts or when spawned
void ATileEventMeshCapturor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATileEventMeshCapturor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATileEventMeshCapturor::SetFocusTarget(AEventActor* NewTargetActor)
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Red, FString::Printf(TEXT("ATileEventMeshCapturor::SetFocusTarget : TileEventMesh : %s"), *NewTargetActor->GetTileEventMesh()->GetName()));
	SetActorTransform(NewTargetActor->GetTileEventMesh()->GetCapturePosition());
	SceneCaptureComponent->ShowOnlyActorComponents(NewTargetActor->GetTileEventMesh());
}