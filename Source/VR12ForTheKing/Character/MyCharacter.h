// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class UCapsuleComponent;
class AHexTile;
class AMyGameModeBase;
class UBattleComponent;
class UStatusComponent;
class UInventoryComponent;
UCLASS()
class VR12FORTHEKING_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();

	void Init(AMyGameModeBase* NewGameMode);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReachToDestination();


public:
	// Getter / Setter
	void SetMoveMode(bool NewMoveMode);
	void SetCurrentTile(AHexTile* NewCurrentTile);

	UFUNCTION(BlueprintCallable)
	void SetDestination(FVector NewDestination, float NewSpeed = 0.0f, float NewRadius = 10.0f);
	AHexTile* GetCurrentTile();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	int32 GetTurnSpeed(const int32 CurrentRoundCount);

	UFUNCTION(BlueprintCallable)
	UTexture2D* GetCharacterImage();
	UFUNCTION(BlueprintCallable)
	void SetCharacterImage(UTexture2D* NewCharacterImage);

	FText GetCharacterName() const;

private:
	void TestRandomizeStatus();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBattleComponent* BattleComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatusComponent* StatusComponent;
private:
	// PlayerInfo
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	UTexture2D* CharacterImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FText CharacterName;

	// Component
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	UInventoryComponent* InventoryComponent;

	AMyGameModeBase* GameMode;

	// Move Var
	UPROPERTY(BlueprintReadWrite, Category = "Status", EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bIsMoveMode = true;
	float ReachSuccessRadius = 10.0f;
	AHexTile* CurrentTile;
	FVector Destination;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float MoveSpeed = 500.0f;
};