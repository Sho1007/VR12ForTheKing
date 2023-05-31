// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusBoardWidget.generated.h"

/**
 * 
 */
class UStatusComponent;
class AMyCharacter;
class UStatusWidget;
class UButton;
UCLASS()
class VR12FORTHEKING_API UStatusBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void UpdateStatus(UStatusComponent* StatusComponent);

public:
	// Getter / Setter
	void SetOwnerCharacter(AMyCharacter* NewOwnerCharacter);
	void SetParent(UStatusWidget* NewParentWidget);
private:
	UFUNCTION()
	void InventoryButtonOnClicked();
	UFUNCTION()
	void StatusButtonOnClicked();
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Inventory;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true, BindWidget))
	UButton* Btn_Status;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category = "Status")
	AMyCharacter* OwnerCharacter;

	UStatusWidget* ParentWidget;
};