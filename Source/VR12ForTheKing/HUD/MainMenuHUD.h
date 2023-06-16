// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

/**
 * 
 */
class UMainMenuWidget;
UCLASS()
class VR12FORTHEKING_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMainMenuHUD(const FObjectInitializer& ObjectInitializer);
protected:
	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

private:
	void InitHUD();


private:
	UPROPERTY(Replicated)
	bool bIsInit;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMainMenuWidget> MainMenuWidgetClass;
	UMainMenuWidget* MainMenuWidget;
};