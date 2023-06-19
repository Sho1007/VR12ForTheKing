// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../VR12ForTheKing.h"
#include "Components/ActorComponent.h"
#include "../VR12ForTheKing.h"
#include "Engine/DataTable.h"
#include "BattleComponent.generated.h"

// Check Chance

USTRUCT(BlueprintType)
struct FAction : public FTableRowBase
{
	GENERATED_BODY()

		UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UTexture2D* Image;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Name;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		FText Discription;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 Power;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CheckCount;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 CheckPercent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EStatusType StatType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EActionType ActionType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EActionRange ActionRange;
};

class AMyCharacter;
class UStatusComponent;
class UActionWidget;
class UBattleWidget;
class UDamageText;
UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VR12FORTHEKING_API UBattleComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBattleComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, CallInEditor)
		void BattleAction();
	void BattleAction_Implementation();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void Attack();
	void Attack_Implementation();

	UFUNCTION(BlueprintCallable)
		bool MeleeAttack();

	UFUNCTION(BlueprintCallable)
		void RangetAttack();

	UFUNCTION(BlueprintCallable)
		void WeakHeal();

	UFUNCTION(BlueprintCallable)
		void Resurrection(AMyCharacter* TargerCharacter);

	UFUNCTION(BlueprintCallable)
		void BackToBattlePos();

	UFUNCTION(BlueprintCallable)
		void CalculateDamage(int32 TargetCheckCount);

	UFUNCTION(BlueprintCallable)
		void GiveDamage();

	void ReceiveDamage(int Damage);

	UFUNCTION(BlueprintCallable)
		bool IsDead();

	UFUNCTION(BlueprintCallable)
		void DoAction(UActionWidget* ActionWidget = nullptr);
	UFUNCTION(BlueprintCallable)
		void DoActionWork(FName TargetActionName);
	UFUNCTION(BlueprintCallable)
		void ReachToDestination();

	void CreateDamageTextWidget();



	//Setter Getter
	UFUNCTION(BlueprintCallable)
		void SetCharacterRotation();

	UFUNCTION(BlueprintCallable)
		void SetFactionType(EFactionType NewFactionType);

	UFUNCTION(BlueprintCallable)
		void SetTargetCamera(AActor* NewTargetCamera);
	UFUNCTION(BlueprintCallable)
		AActor* GetTargetCamera()const;

	UFUNCTION(BlueprintCallable)
		const EFactionType& GetFactionType() const;
	const TArray<FName>& GetActionArray() const;

	void SetActionTarget(AMyCharacter* NewActionTarget);
	
	AMyCharacter* GetActionTarget();
	void EndTurn();

	void SetBaseTransform(FTransform NewBaseTransform);
	void ChanceCoinCheck();
protected:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		EFactionType FactionType;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AActor* TargetCamera;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<FName> ActionArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<bool> ChanceArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		AMyCharacter* ActionTarget;
	
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		bool bIsTurnEnd;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		bool GoBack;

	// Reference
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		bool bGoToTarget;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		FName TargetActionName;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		AMyCharacter* Character;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		FTransform BaseTransform;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		FRotator CharacterRot;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		int32 Damage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		TSubclassOf<UDamageText> DamageTextClass;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		UDamageText* DamageText;
};