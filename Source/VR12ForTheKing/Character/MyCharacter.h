// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "MyCharacter.generated.h"

class UCapsuleComponent;
class AHexTile;
//class AMyGameModeBase;
class UBattleComponent;
class UStatusComponent;
class UInventoryComponent;


USTRUCT(BlueprintType)
struct FCharacterData
{
	GENERATED_BODY()

public:
	FCharacterData()
	{
		CharacterName = FText::FromString(TEXT("Player"));
		//CharacterColor = NewColor;
		// Todo : Change Character Color To Widget
		//CharacterClass = NewClass;
		// Todo : Spawn Character Test Actor with Class
		ControllerIndex = 1;
	}

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FText CharacterName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FColor CharacterColor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FName CharacterClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UTexture2D* CharacterImage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 ControllerIndex;
};

UCLASS()
class VR12FORTHEKING_API AMyCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyCharacter();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void NotifyActorBeginCursorOver() override;
	virtual void NotifyActorEndCursorOver() override;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void ReachToDestination();
	void ReachToDestination_Implementation();

	void InitPlayerCharacter(FCharacterData* NewCharacterData);
public:
	// Getter / Setter
	AMyCharacter* GetActionTarget() const;

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

	int32 GetControllerIndex() const;
	void SetControllerIndex(int32 NewControllerIndex);

private:
	void TestRandomizeStatus();
protected:
	// Component
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBattleComponent* BattleComponent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStatusComponent* StatusComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	UInventoryComponent* InventoryComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	USkeletalMeshComponent* SkeletalMeshComponent;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Component", meta = (AllowPrivateAccess = true))
	UCapsuleComponent* CapsuleComponent;
private:
	// PlayerInfo
	UPROPERTY(Replicated, BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
	FCharacterData CharacterData;

	//AMyGameModeBase* GameMode;

	// Move Var
	UPROPERTY(BlueprintReadWrite, Category = "Status", Replicated, EditAnywhere, meta = (AllowPrivateAccess = true))
	bool bIsMoveMode = true;
	float ReachSuccessRadius = 10.0f;
	AHexTile* CurrentTile;
	FVector Destination;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = true))
	float MoveSpeed = 500.0f;
};