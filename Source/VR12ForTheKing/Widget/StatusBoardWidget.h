// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusBoardWidget.generated.h"

/**
 * 
 */
class UInventoryComponent;
class UStatusComponent;
class AMyCharacter;
class UStatusWidget;
class UButton;
class UInventorySlotButton;
class UProgressBar;
class UTextBlock;
class UUniformGridPanel;
UCLASS()
class VR12FORTHEKING_API UStatusBoardWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

public:
	UFUNCTION(BlueprintCallable)
	void UpdateStatus();
	UFUNCTION()
	void UpdateInventory();
public:
	// Getter / Setter
	void SetOwnerCharacter(AMyCharacter* NewOwnerCharacter);
	AMyCharacter* GetOwnerCharacter() const;
	void SetParent(UStatusWidget* NewParentWidget);
private:
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	UFUNCTION()
	void InventoryButtonOnClicked();
	UFUNCTION()
	void StatusButtonOnClicked();

	UFUNCTION()
	void UpdateCurrentHP(int32 CurrentHP);
	UFUNCTION()
	void UpdateAttackPower(int32 AttackPower);
	UFUNCTION()
	void UpdateEvasion(int32 Evasion);
	UFUNCTION()
	void UpdateResistance(int32 Resistance);
	UFUNCTION()
	void UpdateArmor(int32 Armor);
	UFUNCTION()
	void UpdateLevel(int32 Level);
	
	UFUNCTION()
	void UpdateStrength(int32 Strength);
	UFUNCTION()
	void UpdateVitality(int32 Vitality);
	UFUNCTION()
	void UpdateIntelligence(int32 Intelligence);
	UFUNCTION()
	void UpdateCognition(int32 Cognition);
	UFUNCTION()
	void UpdateTalent(int32 Talent);
	UFUNCTION()
	void UpdateSpeed(int32 Speed);
	UFUNCTION()
	void UpdateLuck(int32 Luck);

private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Inventory;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category = "Status")
	AMyCharacter* OwnerCharacter;
	UStatusWidget* ParentWidget;
	UInventoryComponent* OwnerInventory;

	// Inventory Var
	TArray<UInventorySlotButton*> InventorySlotArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Gold;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot0;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot1;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot2;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot3;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot4;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot5;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot6;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot7;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot8;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UInventorySlotButton* Btn_InvenSlot9;

	// Status Var

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_PlayerName;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_CurrentHP;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UProgressBar* PB_HP;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UProgressBar* PB_EXP;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_AttackPower;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Evasion;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Resistance;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Armor;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Level;
	
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Strength;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Vitality;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Intelligence;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Cognition;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Talent;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Speed;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Luck;
};