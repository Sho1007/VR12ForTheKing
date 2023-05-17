// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleMap.generated.h"

UCLASS()
class VR12FORTHEKING_API ABattleMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Getter / Setter
	const TArray<AActor*>& GetEnemySpawnPosition() const;
	const TArray<AActor*>& GetPlayerSpawnPosition() const;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AActor*> PlayerSpawnPosition;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AActor*> EnemySpawnPosition;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	AActor* PlayerSideCamera;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	AActor* EnemySideCamera;
};
