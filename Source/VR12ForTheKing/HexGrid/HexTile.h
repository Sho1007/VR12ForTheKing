// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HexTile.generated.h"

class UTextRenderComponent;
class UStaticMeshComponent;
UCLASS()
class VR12FORTHEKING_API AHexTile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHexTile();

public:
	void SetParentTile(AHexTile* NewParentTile);
	AHexTile* GetParentTile() { return ParentTile; }
	void SetPos(FIntPoint NewPos);
	const FIntPoint& GetPos() { return Pos; }
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetIsPath(bool bNewIsPath, int NewDistance = 0);

	void ClickTile();
	void UnClickTile();

protected:
	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StaticMeshComponent;
	UPROPERTY(EditDefaultsOnly)
	UTextRenderComponent* TextRenderComponent;

	FIntPoint Pos;
	// A*
	AHexTile* ParentTile;
};
