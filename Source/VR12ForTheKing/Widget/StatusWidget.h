// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusWidget.generated.h"

/**
 * 
 */
class UStatusLayoutWidget;
class UStatusBoardWidget;
class UStatusComponent;
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API UStatusWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	bool UpdateStatusBoard(int BoardIndex, UStatusComponent* StatusComponent);
	void HideWidget();
	void OpenInventory(AMyCharacter* TargetCharacter);
	void OpenStatus(AMyCharacter* TargetCharacter);
public:
	// Getter / Setter
	void SetParentToChild();

	void SetOwnerCharacter(const TArray<AMyCharacter*>& NewCharacterArray);
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard1;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard2;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusBoardWidget* WBP_StatusBoard3;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (BindWidget, AllowPrivateAccess = true))
	UStatusLayoutWidget* WBP_StatusLayout;
};