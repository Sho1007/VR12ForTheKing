// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Engine/DataTable.h"

#include "EventActor.generated.h"

UENUM(BlueprintType)
enum class EEventType : uint8
{
	NONE,
	ENEMY,
	STRUCTURE,
	TOWN,
	MERCHANT,
	DUNGEON,
};

//class AEventMesh;
USTRUCT(BlueprintType)
struct FEventInfo : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	EEventType EventType;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TSubclassOf<AEventActor> EventActorClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText EventName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Discription1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FText Discription2;
	//UPROPERTY(BlueprintReadOnly, EditAnywhere)
	//TSubclassOf<AEventMesh> EventMeshClass;
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

	const FText GetEventName() const;
	const FText GetDiscription1() const;
	const EEventType GetEventType() const;

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FEventInfo EventInfo;
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UBoxComponent* BoxCollisionComponent;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UChildActorComponent* EventMeshComponent;
};
