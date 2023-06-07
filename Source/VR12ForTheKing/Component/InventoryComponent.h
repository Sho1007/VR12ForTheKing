// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "../Event/TileEventManager.h"
#include "../Item/ItemBase.h"
#include "InventoryComponent.generated.h"

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
	bool EquipItem(int32 ItemIndex);
	UFUNCTION(BlueprintCallable)
	bool UnEquipItem(EEquipmentType TargetSlot);
	UFUNCTION(BlueprintCallable)
	bool UseItem(int32 ItemIndex);
public:
	// Getter / Setter
	int32 GetCurrentGold() const;
	TArray<FItemInstance>& GetItemArray();
	FItem* GetItemInfo(FName NewItemRow);
	FItem* GetItemInfoAtInventory(int32 ItemIndex);
	TArray<FItemInstance>& GetEquipmentSlot();

public:
	FDele_Single UpdateInventory;

private:
	void AttachItemOption(EEquipmentType NewEquipmentType);
	void DetachItemOption(EEquipmentType NewEquipmentType);
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FItemInstance> ItemArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UDataTable* ItemDataTable;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	int32 Gold;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TArray<FItemInstance> EquipmentSlot;
};