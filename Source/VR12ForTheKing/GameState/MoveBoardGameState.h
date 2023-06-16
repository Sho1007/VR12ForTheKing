// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "MoveBoardGameState.generated.h"

/**
 * 
 */
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API AMoveBoardGameState : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	TArray<AMyCharacter*>& GetPlayerCharacterArray();
private:
	UPROPERTY(meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> PlayerCharacterArray;
};
