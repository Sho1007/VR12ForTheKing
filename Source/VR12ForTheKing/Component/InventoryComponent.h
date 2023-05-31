// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../Event/TileEventManager.h"
#include "InventoryComponent.generated.h"

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

	// Option
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusArmor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusCognition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusEvasion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 BonusFocus;
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
	TArray<FItemInstance>& GetItemArray();
private:
	void AttachItemOption(EEquipmentType TargetEuipmentType);
	void DetachItemOption(EEquipmentType TargetEuipmentType);
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