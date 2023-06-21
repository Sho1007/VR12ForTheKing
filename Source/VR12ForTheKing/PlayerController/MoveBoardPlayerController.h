// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "GameFramework/PlayerController.h"
#include "MoveBoardPlayerController.generated.h"

/**
 * 
 */
class AHexTile;
class UInputMappingContext;
class UInputAction;
class AMyCharacter;
UCLASS()
class VR12FORTHEKING_API AMoveBoardPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;
	virtual void BeginPlay() override;
public:
	AMoveBoardPlayerController();

	UFUNCTION(Client, Reliable)
	void MoveCamera(FTransform TargetCameraTransform);
	void MoveCamera_Implementation(FTransform TargetCameraTransform);

	UFUNCTION(Server, Reliable)
	void ReadyToPlay();
	void ReadyToPlay_Implementation();

	UFUNCTION(Server, Reliable)
	void DoEventAction(ETileEventActionType NewEventActionType);
	void DoEventAction_Implementation(ETileEventActionType NewEventActionType);
	
	UFUNCTION(Server, Reliable)
	void DoBattleAction(FName ActionName, AMyCharacter* DeadPlayer);
	void DoBattleAction_Implementation(FName ActionName, AMyCharacter* DeadPlayer);

	UFUNCTION(Client, Reliable)
	void SetBattleTurnArray(const TArray<AMyCharacter*>& NewBattleTurnArray);
	void SetBattleTurnArray_Implementation(const TArray<AMyCharacter*>& NewBattleTurnArray);

	UFUNCTION(Client, Reliable)
	void StartUpdateChanceSlot(int32 CoinSize, EStatusType StatusType, const TArray<bool>& NewChanceArray);
	void StartUpdateChanceSlot_Implementation(int32 CoinSize, EStatusType StatusType, const TArray<bool>& NewChanceArray);

	UFUNCTION(Client, Reliable)
	void InitBattleWidget(AMyCharacter* TargetCharacter);
	void InitBattleWidget_Implementation(AMyCharacter* TargetCharacter);

	UFUNCTION(Client, Reliable)
	void HideBattleWidget();
	void HideBattleWidget_Implementation();

	UFUNCTION(Client, Reliable)
	void ChangeToVictoryWidget();
	void ChangeToVictoryWidget_Implementation();

	UFUNCTION(Client, Reliable)
	void DeleteHeartCount();
	void DeleteHeartCount_Implementation();

	UFUNCTION(Client, Reliable)
	void AddUnitToImageArray(const TArray<AMyCharacter*>& NewImageArray);
	void AddUnitToImageArray_Implementation(const TArray<AMyCharacter*>& NewImageArray);
public:
	// Getter / Setter

	void SetIsOnWidget(bool bNewIsOnWidget);
	UFUNCTION(Server, Reliable)
	void SetEndTile(AHexTile* NewEndTile);
	void SetEndTile_Implementation(AHexTile* NewEndTile);

	AMyCharacter* GetActionTarget() const;
	UFUNCTION(Server, Reliable)
	void SetActionTarget(AMyCharacter* NewActionTarget);
	void SetActionTarget_Implementation(AMyCharacter* NewActionTarget);

	void SetFocusActor(AMyCharacter* NewFocusActor);
	void ResetFocusActor(AMyCharacter* NewFocusActor);

private:
	void InitPlayerController();
	void LeftClickOnPressed();
	UFUNCTION(Server, Reliable)
	void Req_LeftClick();
	void Req_LeftClick_Implementation();
private:
	bool bIsInit;
	bool bIsOnWidget;

	UPROPERTY(Replicated, meta = (AllowPrivateAccess = true))
	AMyCharacter* ActionTarget;
	AMyCharacter* FocusActor;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UInputMappingContext* IMC_Default;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UInputAction* IA_LeftClick;
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	UInputAction* IA_RightClick;

	UPROPERTY(Replicated, meta = (AllowPrivateAccess = true))
	int32 ControllerIndex;
};