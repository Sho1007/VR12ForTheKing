// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MoveBoardGameMode.generated.h"

/**
 * 
 */

class UBattleManagerComponent;
class UMoveManagerComponent;
class UHexGridManager;
class UTileEventManager;

UCLASS()
class VR12FORTHEKING_API AMoveBoardGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMoveBoardGameMode();

protected:
	virtual void BeginPlay() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;
	virtual void HandleSeamlessTravelPlayer(AController*& C) override;
};