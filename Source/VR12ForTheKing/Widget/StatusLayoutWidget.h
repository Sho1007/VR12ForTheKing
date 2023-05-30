// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusLayoutWidget.generated.h"

/**
 * 
 */
class AMyCharacter;
class UTextBlock;
class UStatusWidget;
UCLASS()
class VR12FORTHEKING_API UStatusLayoutWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitWidget(AMyCharacter* NewTargetCharacter);
public:
	// Getter / Setter
	void SetParent(UStatusWidget* NewParentWidget);
private:
	AMyCharacter* TargetCharacter;

	UStatusWidget* ParentWidget;

	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_PlayerName;
	
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Strength;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Vitality;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Intelligence;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Cognition;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Talent;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Speed;
	UPROPERTY(BlueprintReadWrite, EditInstanceOnly, Category = "Status", meta = (AllowPrivateAccess = true, BindWidget))
	UTextBlock* TB_Luck;
};
