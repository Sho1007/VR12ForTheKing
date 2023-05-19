// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MoveManagerComponent.generated.h"


class UMoveWidget;
UCLASS(Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UMoveManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMoveManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
public:
	void Init();
private:
	void CreateMoveWidget();

	void PrepareTurn();
	void ExecuteTurn();
	void FinishTurn();
public:
	// Getter / Setter
	const UMoveWidget* GetMoveWidget() const;
private:
	int32 Turn;
	int32 Day;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<UMoveWidget> MoveWidgetClass;
	UMoveWidget* MoveWidget;
};
