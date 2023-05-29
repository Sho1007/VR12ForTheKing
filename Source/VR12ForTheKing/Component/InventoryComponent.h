// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryComponent.generated.h"

UENUM(BlueprintType)
enum class EItemRarity : uint8
{
	NONE,
	COMMON,
	UNCOMMON,
	RARE,
	ARTIFACT,
	SIZE,
};

UENUM(BlueprintType)
enum class EItemType : uint8
{
	NONE,
	CONSUMABLE,
	EQUIPMENT,
	SIZE,
};

UENUM(BlueprintType)
enum class EEqiupmentType : uint8
{
	NONE,
	WEAPON,
	SHIELD,
	HEADGEAR,
	ARMOR,
	FOOTWEAR,
	NECKLACE,
	TRINKET,
	PIPE,
	SIZE,
};

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
	EEqiupmentType EqiupmentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxStackCount;
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
};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UInventoryComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void AddItem(const FName NewItemRow, int32 NewItemCount);
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FItemInstance> ItemArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UDataTable* ItemDataTable;
};