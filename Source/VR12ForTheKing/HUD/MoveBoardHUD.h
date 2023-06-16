// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MoveBoardHUD.generated.h"

/**
 * 
 */
class UStatusWidget;
class UMoveWidget;
class UTileEventWidget;

UCLASS()
class VR12FORTHEKING_API AMoveBoardHUD : public AHUD
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
private:
	void InitHUD();
public:
	// Getter / Setter
	UStatusWidget* GetStatusWidget() const;
	UMoveWidget* GetMoveWidget() const;
	UTileEventWidget* GetTileEventWidget() const;

private:
	UPROPERTY(Replicated, meta = (AllowPrivateAccess = true))
	bool bIsInit;

	// StatusWidget
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UStatusWidget> StatusWidgetClass;
	UStatusWidget* StatusWidget;
	// MoveWidget
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMoveWidget> MoveWidgetClass;
	UMoveWidget* MoveWidget;
	// TileEventWidget
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UTileEventWidget> TileEventWidgetClass;
	UTileEventWidget* TileEventWidget;
};