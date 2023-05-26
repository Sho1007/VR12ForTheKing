// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventStaticMesh.h"

ATileEventStaticMesh::ATileEventStaticMesh()
{
	StaticMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>("StaticMeshComponent");
	StaticMeshComponent->SetupAttachment(RootComponent);
}
