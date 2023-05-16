// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Event/EventActor.h"
#include "EnemyEventActor.generated.h"

/**
 * 
 */
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API AEnemyEventActor : public AEventActor
{
	GENERATED_BODY()
	
public:
	AEnemyEventActor();

	const int32 GetEnemyNum() const;
	const TArray<TSubclassOf<AMyCharacter>>& GetEnemyArray() const;

	UFUNCTION(BlueprintCallable)
	void StartBattle();
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<TSubclassOf<AMyCharacter>> EnemyArray;
};