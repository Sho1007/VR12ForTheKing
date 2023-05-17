// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"

#include "EventActor.generated.h"

USTRUCT(BlueprintType)
struct FEventActionInfo
{
	GENERATED_BODY()
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	ETileEventActionType TileEventActionType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ButtonName;
};

class ATileEventMesh;
class AMyCharacter;
USTRUCT(BlueprintType)
struct FEventInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEventType EventType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AEventActor> EventActorClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText EventName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Discription1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Discription2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<ATileEventMesh> TileEventMeshClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FEventActionInfo> EventActionButtonArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<TSubclassOf<AMyCharacter>> EnemyClassArray;
};

class UBoxComponent;
class UChildActorComponent;
UCLASS()
class VR12FORTHEKING_API AEventActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEventActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetEventInfo(const FEventInfo& NewEventInfo);

	const FText GetEventName() const;
	const FText GetDiscription1() const;
	const EEventType GetEventType() const;
	const FEventInfo& GetEventInfo() const;
	ATileEventMesh* GetTileEventMesh() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FEventInfo EventInfo;
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UBoxComponent* BoxCollisionComponent;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	ATileEventMesh* TileEventMesh;
};