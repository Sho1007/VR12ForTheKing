// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "GameFramework/Actor.h"
#include "Engine/DataTable.h"
#include "ItemBase.generated.h"

class AItemBase;
class UTexture2D;
USTRUCT(BlueprintType)
struct FItem : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText ItemName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemRarity ItemRarity;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EItemType ItemType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxStackCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemIcon;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* ItemImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString ItemDiscription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AItemBase> ItemClass;

	// Equipment
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEquipmentType EquipmentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> ActionArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsTwoHand;

	// Option
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusArmor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusCognition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusEvasion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusMaxFocus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusIntelligence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusLuck;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusResistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusSpeed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusStrength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusTalent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusVitality;
};

USTRUCT(BlueprintType)
struct FItemInstance
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName ItemRow;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentStackCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxStackCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsEquiped;
};

class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API AItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemBase();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Use(AMyCharacter* OwnerCharacter);
};