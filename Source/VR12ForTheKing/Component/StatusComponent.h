// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

USTRUCT(BlueprintType)
struct FCharacterStatus
{
	GENERATED_BODY()

public:
	// Status
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Armor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cognition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Evasion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Focus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Intelligence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Luck;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Resistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Strength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Talent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Vitality;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentMP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxMP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackPower;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsMagicalAttackPower;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level;
};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	FCharacterStatus& GetCharacterStatus();
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess =  true))
	FCharacterStatus CharacterStatus;
};