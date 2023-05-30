// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../Event/TileEventManager.h"
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
enum class EEquipmentType : uint8
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

	// Equipment
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	EEquipmentType EquipmentType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<FName> ActionArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsTwoHand;
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
	
	UFUNCTION(BlueprintCallable)
	bool EquipItem(int ItemIndex);
	UFUNCTION(BlueprintCallable)
	bool UnEquipItem(EEquipmentType TargetSlot);
public:
	// Getter / Setter
	int32 GetCurrentGold() const;
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FItemInstance> ItemArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UDataTable* ItemDataTable;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int32 Gold;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<int32> EquipmentSlot;
};