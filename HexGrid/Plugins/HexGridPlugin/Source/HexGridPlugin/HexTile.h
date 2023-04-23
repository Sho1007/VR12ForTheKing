// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexTile.generated.h"

UENUM()
enum class EHexTileType : uint8
{
	INVALID,
	GRASS,
	WATER,
	SIZE UMETA(Hidden)
};

UCLASS()
class HEXGRIDPLUGIN_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	EHexTileType TileType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Tile")
	UStaticMeshComponent* StaticMeshComponent;
};
