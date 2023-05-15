// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Event/TileEventMesh.h"
#include "TileEventSkeletalMesh.generated.h"

/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API ATileEventSkeletalMesh : public ATileEventMesh
{
	GENERATED_BODY()
	
	ATileEventSkeletalMesh();
	
protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	USkeletalMeshComponent* SkeletalMeshComponent;
};
