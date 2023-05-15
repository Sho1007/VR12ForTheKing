// Fill out your copyright notice in the Description page of Project Settings.


#include "../Event/TileEventSkeletalMesh.h"
#include "Components/ArrowComponent.h"

ATileEventSkeletalMesh::ATileEventSkeletalMesh()
{
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SkeletalMeshComponent->SetupAttachment(RootComponent);
	CapturePosition->SetupAttachment(SkeletalMeshComponent);
}
