// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleManagerComponent.generated.h"


class UBattleWidget;
class AMyCharacter;
class ABattleMap;
class UBattleComponent;
class UVictoryWidget;
class UVictoryWidgetSlot;
struct FItemInstance;

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class VR12FORTHEKING_API UBattleManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UBattleManagerComponent();



protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddEnemyClass(const TSubclassOf<AMyCharacter> NewEnemyClass);
	void AddPlayerCharacter(AMyCharacter* NewPlayerCharacter);

	void DebugInfo();

	void InitBattle(AActor* BattleTile);
	void MoveToNextUnitTurn();
	void RemoveDeadUnitFromArray(AMyCharacter* TargetCharacter);
	void ResetActionTargetWhenEnemyDead();
	void ResurrectCharacter(AMyCharacter* ResurrectCharacter);

public:
	// Getter / Setter
	bool SetGameMode(AGameModeBase* NewGameMode);
	bool IsBattle();
	AMyCharacter* GetPlayerCharacter(int32 Index);
	int32 GetPlayerCharacterArrayNum();
	UBattleWidget* GetBattleWidget();
	void ReceiveReward();
private:
	// Battle Process
	bool SpawnEnemy();
	bool TeleportCharacter();
	void MoveCamera(FTransform TargetCameraTransform);
	void MoveLerpCamera(FTransform NewTargetCameraTransform);
	UFUNCTION()
	void LerpTimerFunction();
	void CalculateTurn();
	void InitUnitTurn();
	void CreateBattleWidget();
	void CreateVictoryWidget();

	void EndBattle();
	void MoveToNextStage();
	void GameOver();
private:
	// Battle Var
	TArray<TSubclassOf<AMyCharacter>> EnemyClassArray;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> EnemyCharacterArray;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> PlayerCharacterArray;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> TargetPlayerArray;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<FItemInstance> RewardArray;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		int32 DeadEnemyCount;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		int32 DeadPlayerCount;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		int32 CurrentBattleRound;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> BattleTurnArray;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TArray<AMyCharacter*> UseBattleTurnArray;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess = true))
		ABattleMap* BattleMap;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		TArray<ABattleMap*> BattleMapArray;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<ABattleMap> BattleMapClass;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		int32 SpawnEnemyIndex;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		int32 NextTurnIndex;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		int32 MapIndex;
	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta = (AllowPrivateAccess = true))
		int32 VictoryCount;

	FVector CurrentLocation;
	FRotator CurrentRotation;

	FVector TargetLocation;
	FRotator TargetRotation;
	FTimerHandle CameraLerpTimerHandle;

	// BattleWidget Var
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UBattleWidget> BattleWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UVictoryWidget> VictoryWidgetClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		TSubclassOf<UVictoryWidgetSlot> VictoryWidgetSlotClass;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		UBattleWidget* BattleWidget;
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
		UVictoryWidget* VictoryWidget;

	AGameModeBase* GameMode;

	bool bIsBattle;
	//function


};