// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../VR12ForTheKing.h"
#include "Engine/DataTable.h"
#include "BattleComponent.generated.h"

// Check Chance

UENUM(BlueprintType)
enum class EFactionType : uint8
{
	Player,
	Enemy
};

UENUM(BlueprintType)
enum class EActionType : uint8
{
	Attack,
	Buff
};

UENUM(BlueprintType)
enum class EActionRange : uint8
{
	Single,
	All,
};

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
struct FAction : public FTableRowBase
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
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EActionType ActionType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EActionRange ActionRange;
};

class AMyCharacter;
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, CallInEditor)
	void BattleAction();
	void BattleAction_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void Attack();
	void Attack_Implementation();

	UFUNCTION(BlueprintCallable)
	void SetFactionType(EFactionType NewFactionType);

protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EFactionType FactionType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> ActionArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	AMyCharacter* ActionTarget;
};