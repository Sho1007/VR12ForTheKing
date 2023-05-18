// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

/**
 * 
 */
class UInventoryWidget;
class UStatusDetailWidget;
class UStatusBoardWidget;
class UStatusComponent;
UCLASS()
class VR12FORTHEKING_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool UpdateStatusBoard(int BoardIndex, UStatusComponent* StatusComponent);
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UInventoryWidget* WBP_Inventory;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusDetailWidget* WBP_StatusDetail;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard3;
};