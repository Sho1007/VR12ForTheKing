// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "MyCharacter.generated.h"

UCLASS()
class VR12FORTHEKING_API AMyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Armor;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Awareness;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Evasion;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Focus;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Intelligence;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Luck;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Resistance;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Speed;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Strength;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Talent;
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	float Vitality;
};
