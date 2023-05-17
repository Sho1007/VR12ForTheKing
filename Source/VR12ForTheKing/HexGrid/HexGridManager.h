// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexGridManager.generated.h"

class AHexTile;



USTRUCT(BlueprintType)
struct FTileRow
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	TArray<AHexTile*> TileArray;
};

USTRUCT(BlueprintType)
struct FTileNode
{
	GENERATED_BODY()
	
	FTileNode() {}
	FTileNode(AHexTile* NewTile, float NewG, float NewH)
		: Tile(NewTile), G(NewG), H(NewH)
	{
	}

	AHexTile* Tile;
	float G;
	float H;
};

UCLASS()
class VR12FORTHEKING_API AHexGridManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexGridManager();

	void InitGirdInfo(TSubclassOf<AHexTile> NewHexTileClass, int32 NewWidth, int32 NewHeight, float NewXOffset, float NewXStartOffset, float NewYOffset);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, CallInEditor)
	void CreateGrid();

public:
	// A* Algorithm Function
	TArray<AHexTile*> GetPath();
	AHexTile* GetNextPath();
	AHexTile* GetTile(int X, int Y);

	void SetStartTile(AHexTile* NewStartTile);
	void SetEndTile(AHexTile* NewEndTile, int32 MovableCount);

	// Event Function
	void SpawnEnemy(FIntPoint Center);
	void FindNeighborTiles(TArray<AHexTile*>& NewNeighborTileArray, AHexTile* CurrentTile, int32 distance = 1);
private:
	void FindPath(TArray<AHexTile*>& OutArray);
	int GetIndex(FIntPoint Pos);
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AHexTile> HexTileClass;

	TArray<FTileRow> HexGrid;
	TArray<AHexTile*> CurrentPath;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 Width;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	int32 Height;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float XOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float XStartOffset;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float YOffset;

private:
	// A* Algorithm
	AHexTile* StartTile;
	AHexTile* EndTile;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	float FindAdjOffset = 350;

	// Move Var
	int32 CurrentPathIndex;
};
