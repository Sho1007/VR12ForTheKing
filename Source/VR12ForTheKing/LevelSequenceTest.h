// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelSequenceTest.generated.h"



class ALevelSequenceActor;

UCLASS()
class VR12FORTHEKING_API ALevelSequenceTest : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelSequenceTest();

	UFUNCTION(CallinEditor)
		void PlayLevelSequence();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		ALevelSequenceActor* TestLevelSequence;

};