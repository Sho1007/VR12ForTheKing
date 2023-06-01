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
	bool UpdateStatusBoard(int BoardIndex);
	void HideWidget();
	void OpenInventory(AMyCharacter* TargetCharacter);
	void OpenStatus(AMyCharacter* TargetCharacter);

public:
	UFUNCTION()
	void UpdateStrength(UStatusBoardWidget* TargetBoard, int32 Strength);
	UFUNCTION()
	void UpdateVitality(UStatusBoardWidget* TargetBoard, int32 Vitality);
	UFUNCTION()
	void UpdateIntelligence(UStatusBoardWidget* TargetBoard, int32 Intelligence);
	UFUNCTION()
	void UpdateCognition(UStatusBoardWidget* TargetBoard, int32 Cognition);
	UFUNCTION()
	void UpdateTalent(UStatusBoardWidget* TargetBoard, int32 Talent);
	UFUNCTION()
	void UpdateSpeed(UStatusBoardWidget* TargetBoard, int32 Speed);
	UFUNCTION()
	void UpdateLuck(UStatusBoardWidget* TargetBoard, int32 Luck);

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