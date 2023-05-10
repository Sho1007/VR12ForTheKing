// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Event/EventActor.h"
#include "EnemyEventActor.generated.h"

/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AEnemyEventActor : public AEventActor
{
	GENERATED_BODY()
	
public:
	AEnemyEventActor();

	const int32 GetEnemyNum() const;
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<AActor*> EnemyArray;
};
