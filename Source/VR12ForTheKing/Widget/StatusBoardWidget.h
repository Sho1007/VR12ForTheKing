// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StatusBoardWidget.generated.h"

/**
 * 
 */
class UStatusComponent;
UCLASS()
class VR12FORTHEKING_API UStatusBoardWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void UpdateStatus(UStatusComponent* StatusComponent);

private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true), Category = "Status")
	int PlayerMaxHP;
};
