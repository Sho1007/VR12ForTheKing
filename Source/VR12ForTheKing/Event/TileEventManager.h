// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileEventManager.generated.h"

class UDataTable;
class AEventActor;
class AHexTile;
class ATileEventMeshCapturor;
UCLASS()
class VR12FORTHEKING_API ATileEventManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileEventManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Getter / Stter
	UDataTable* GetDataTable();
	const float GetEventOccurChance() const;
	AEventActor* SetTileEvent(AHexTile* NewHexTile);
	AEventActor* GetTileEvent() const;


private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UDataTable* EventDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float EventOccurChance = 0.2f;

	AEventActor* CurrentTileEvent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<ATileEventMeshCapturor> TileEventMeshCapturorClass;
	ATileEventMeshCapturor* TileEventMeshCapturor;
};
