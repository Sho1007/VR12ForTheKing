// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

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
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	EEventType EventType;
private:
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UBoxComponent* BoxCollisionComponent;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UChildActorComponent* EventMeshComponent;

	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	FText EventName;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	FText Discription1;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	FText Discription2;
};
