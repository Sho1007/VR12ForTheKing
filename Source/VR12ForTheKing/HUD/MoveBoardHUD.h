// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "GameFramework/HUD.h"
#include "MoveBoardHUD.generated.h"

/**
 * 
 */
class UStatusWidget;
class UMoveWidget;
class UTileEventWidget;
class AEventActor;
class AMyCharacter;
class UBattleWidget;
class UTurnWidget;
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
	// TileEventWidget
	void InitTileEventWidget(AEventActor* NewTileEvent);

	// BattleWidget
	void ChangeToBattleWidget();

	void SetBattleTurnArray(TArray<AMyCharacter*>& NewBattleTrunAray);
	void StartUpdateChanceSlot(int32 CoinSize, EStatusType StatusType, const TArray<bool>& NewChanceArray);

	void InitBattleWidget(AMyCharacter* TargetCharacter);
	void HideBattleWidget();
	void ChangeToVictoryWidget();

	// TurnWidget
	void DeleteHeartCount();
	void AddUnitToImageArray(const TArray<AMyCharacter*>& NewImageArray);
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
	// BattleWidget
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UBattleWidget> BattleWidgetClass;
	UBattleWidget* BattleWidget;
	// Widget Var
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<UTurnWidget> TurnWidgetClass;
	UTurnWidget* TurnWidget;
};