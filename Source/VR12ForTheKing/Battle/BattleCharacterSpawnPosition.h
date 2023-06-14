// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleCharacterSpawnPosition.generated.h"

UCLASS()
class VR12FORTHEKING_API ABattleCharacterSpawnPosition : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleCharacterSpawnPosition();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Getter / Setter
	UFUNCTION(BlueprintCallable)
	 AActor* GetCameraPosition() const;
private:
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = true))
	AActor* CameraPosition;
};
