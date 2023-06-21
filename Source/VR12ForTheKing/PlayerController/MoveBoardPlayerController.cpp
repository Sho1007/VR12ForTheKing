// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerController/MoveBoardPlayerController.h"

#include "Net/UnrealNetwork.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"

#include "Camera/CameraComponent.h"

#include "../GameState/MoveBoardGameState.h"
#include "../HUD/MoveBoardHUD.h"
#include "../Character/MyCharacter.h"

AMoveBoardPlayerController::AMoveBoardPlayerController()
	: Super()
{
	bEnableMouseOverEvents = true;
	bIsOnWidget = false;
}

void AMoveBoardPlayerController::MoveCamera_Implementation(FTransform TargetCameraTransform)
{
	GetPawn()->SetActorLocation(TargetCameraTransform.GetLocation());
	GetPawn()->FindComponentByClass<UCameraComponent>()->SetWorldRotation(TargetCameraTransform.GetRotation());
}

void AMoveBoardPlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMoveBoardPlayerController, ControllerIndex);
	DOREPLIFETIME(AMoveBoardPlayerController, ActionTarget);
}

void AMoveBoardPlayerController::BeginPlay()
{
	Super::BeginPlay();

	if (IsLocalController())
	{
		if (bIsInit == false)
		{
			bIsInit = true;
			InitPlayerController();
		}
	}
}

void AMoveBoardPlayerController::ReadyToPlay_Implementation()
{
	GetWorld()->GetGameState<AMoveBoardGameState>()->SetReadyPlayer();
}

void AMoveBoardPlayerController::DoEventAction_Implementation(ETileEventActionType NewEventActionType)
{
	GetWorld()->GetGameState<AMoveBoardGameState>()->DoEventAction(this, NewEventActionType);
}

void AMoveBoardPlayerController::DoBattleAction_Implementation(FName ActionName, AMyCharacter* DeadPlayer)
{
	GetWorld()->GetGameState<AMoveBoardGameState>()->DoBattleAction(ActionName, DeadPlayer);
}

void AMoveBoardPlayerController::SetActionTarget_Implementation(AMyCharacter* NewActionTarget)
{
	ActionTarget = NewActionTarget;
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::SetActionTarget : %s -> %s"), *this->GetName(), *ActionTarget->GetName()));
}

void AMoveBoardPlayerController::SetFocusActor(AMyCharacter* NewFocusActor)
{
	FocusActor = NewFocusActor;
}

void AMoveBoardPlayerController::ResetFocusActor(AMyCharacter* NewFocusActor)
{
	if (FocusActor == NewFocusActor) FocusActor = nullptr;
}

void AMoveBoardPlayerController::SetBattleTurnArray_Implementation(const TArray<AMyCharacter*>& NewBattleTurnArray)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::SetBattleTurnArray")));
	/*GetHUD<AMoveBoardHUD>()->SetBattleTurnArray(NewBattleTurnArray);*/
}

void AMoveBoardPlayerController::StartUpdateChanceSlot_Implementation(int32 CoinSize, EStatusType StatusType, const TArray<bool>& NewChanceArray)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::StartUpdateChanceSlot")));
	GetHUD<AMoveBoardHUD>()->StartUpdateChanceSlot(CoinSize, StatusType	,NewChanceArray);
}

void AMoveBoardPlayerController::InitBattleWidget_Implementation(AMyCharacter* TargetCharacter)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::InitBattleWidget")));
	GetHUD<AMoveBoardHUD>()->InitBattleWidget(TargetCharacter);
}

void AMoveBoardPlayerController::HideBattleWidget_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::HideBattleWidget")));
	GetHUD<AMoveBoardHUD>()->HideBattleWidget();
}

void AMoveBoardPlayerController::ChangeToVictoryWidget_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::ChangeToVictoryWidget")));
	GetHUD<AMoveBoardHUD>()->ChangeToVictoryWidget();
}

void AMoveBoardPlayerController::DeleteHeartCount_Implementation()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::DeleteHeartCount")));
	GetHUD<AMoveBoardHUD>()->DeleteHeartCount();
}

void AMoveBoardPlayerController::AddUnitToImageArray_Implementation(const TArray<AMyCharacter*>& NewImageArray)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::AddUnitToImageArray")));
	GetHUD<AMoveBoardHUD>()->AddUnitToImageArray(NewImageArray);
}

void AMoveBoardPlayerController::SetIsOnWidget(bool bNewIsOnWidget)
{
	bIsOnWidget = bNewIsOnWidget;

	// Todo : Disable Path;
}

void AMoveBoardPlayerController::SetEndTile_Implementation(AHexTile* NewEndTile)
{
	if (bIsOnWidget == true) return;

	AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(GameState != nullptr);
	GameState->SetEndTile(this, NewEndTile);
}

AMyCharacter* AMoveBoardPlayerController::GetActionTarget() const
{
	return ActionTarget;
}

void AMoveBoardPlayerController::InitPlayerController()
{
	UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (IMC_Default && SubSystem)
	{
		SubSystem->AddMappingContext(IMC_Default, 0);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("SubSystem or IMC is not valid!"));
	}

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (EnhancedInputComponent)
	{
		//UE_LOG(LogTemp, Warning, TEXT("%s"), *EnhancedInputComponent->GetName());
		checkf(IA_LeftClick != nullptr, TEXT("IA_LeftClick is not valid!"));
		EnhancedInputComponent->BindAction(IA_LeftClick, ETriggerEvent::Started, this, &AMoveBoardPlayerController::LeftClickOnPressed);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("EnhancedInputComponent is not valid!"));
	}
}

void AMoveBoardPlayerController::LeftClickOnPressed()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5, FColor::Yellow, FString::Printf(TEXT("AMoveBoardPlayerController::LeftClickOnPressed")));

	if (FocusActor)
	{
		// if (ActionTarget) ActionTarget->SetFocusWidget(false);
		// Todo : FocusActor->SetFocusWidget(true);
		SetActionTarget(FocusActor);
	}

	Req_LeftClick();
}

void AMoveBoardPlayerController::Req_LeftClick_Implementation()
{
	AMoveBoardGameState* GameState = GetWorld()->GetGameState<AMoveBoardGameState>();
	check(GameState != nullptr);
	GameState->MoveCharacter(this);
}