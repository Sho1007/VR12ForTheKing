// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Event/TileEventMesh.h"
#include "TileEventStaticMesh.generated.h"

/**
 * 
 */
class UStaticMeshComponent;
UCLASS()
class VR12FORTHEKING_API ATileEventStaticMesh : public ATileEventMesh
{
	GENERATED_BODY()
	
public:
	ATileEventStaticMesh();

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UStaticMeshComponent* StaticMeshComponent;
};
