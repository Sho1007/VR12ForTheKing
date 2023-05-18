// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "VR12ForTheKing.h"
#include "GameFramework/Pawn.h"
#include "MyPlayerPawn.generated.h"

class UCameraComponent;
UCLASS()
class VR12FORTHEKING_API AMyPlayerPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AMyPlayerPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
	UCameraComponent* CameraComponent;
};
