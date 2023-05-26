// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class AMyGameModeBase;
class AHexTile;
class AMyCharacter;
class AEventActor;
class UActionWidget;
/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AMyPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	const FText GetPlayerName() const;
private:
	void LeftClickPressed();
	void RightClickPressed();
	void CheckFocusActor();
	AActor* GetHitActor();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputMappingContext* IMC_Default;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* IA_LeftClick;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UInputAction* IA_RightClick;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float LineTraceDistance = 300.0f;

	AHexTile* SelectTile;

	// Event Var
	AEventActor* EventActor;

	UActionWidget* HoveredActionWidget;

private:
	AMyGameModeBase* GameMode;
	FText PlayerName = FText::FromString(FString("Player"));
};
