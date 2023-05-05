// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleComponent.generated.h"

UENUM(BlueprintType)
enum class EStatusType : uint8
{
	Armor,
	Awareness,
	Evasion,
	Focus,
	Intelligence,
	Luck,
	Resistance,
	Speed,
	Strength,
	Talent,
	Vitality,
};

USTRUCT(BlueprintType)
struct FAction
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* Image;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText Discription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Power;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CheckPercent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EStatusType StatType;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UBattleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FAction> ActionArray;
};
