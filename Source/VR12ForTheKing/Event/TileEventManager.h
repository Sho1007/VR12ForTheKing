// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TileEventManager.generated.h"

class UDataTable;
class AEventActor;
class AHexTile;
class ATileEventMeshCapturor;
class UTileEventWidget;
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VR12FORTHEKING_API UTileEventManager : public UActorComponent
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	UTileEventManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	void SpawnEvent(AHexTile* CenterTile);
	void SetFocusTarget(AActor* NewActor);
public:
	// Getter / Stter
	UDataTable* GetEventDataTable();
	UDataTable* GetActionDataTable();
	const float GetEventOccurChance() const;
	AEventActor* SetCurrentTileEvent(AHexTile* NewHexTile);
	AEventActor* GetTileEvent() const;

	void HideWidget();

private:
	void InitAndShowEventDiscription();
	void CreateTileEventWidget();

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UDataTable* EventDataTable;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UDataTable* ActionDataTable;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	float EventOccurChance = 0.2f;

	AEventActor* CurrentTileEvent;

	AEventActor* CurrentFocusEvent;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<ATileEventMeshCapturor> TileEventMeshCapturorClass;
	ATileEventMeshCapturor* TileEventMeshCapturor;

	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UTileEventWidget> TileEventWidgetClass;
	UTileEventWidget* TileEventWidget;
};