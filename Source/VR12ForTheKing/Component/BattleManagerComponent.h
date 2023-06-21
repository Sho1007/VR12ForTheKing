// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleManagerComponent.generated.h"

class AMyCharacter;
class ABattleMap;
class UBattleComponent;
class ALevelSequenceActor;
class UDataTable;
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
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	UFUNCTION(CallinEditor)
	void PlayLevelSequnce();

	void PlayAnimation(FName TargetAnimName);
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddEnemyClass(const TSubclassOf<AMyCharacter> NewEnemyClass);
	void AddPlayerCharacter(AMyCharacter* NewPlayerCharacter);

	void DebugInfo();

	void DoBattleAction(FName ActionName, AMyCharacter* DeadPlayer);
	void DoBattleActionWork();
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
	UDataTable* GetPlayerAnimDataTable();
	void ReceiveReward();
	AMyCharacter* GetCurrentTurnCharacter() const;
private:
	// Battle Process
	UFUNCTION(Server, Reliable)
	void SpawnEnemy();
	void SpawnEnemy_Implementation();
	bool TeleportCharacter();

	UFUNCTION(NetMulticast, Reliable)
	void MoveLerpCamera(FTransform NewTargetCameraTransform);
	void MoveLerpCamera_Implementation(FTransform NewTargetCameraTransform);
	UFUNCTION()
	void LerpTimerFunction();
	void CalculateTurn();
	/*void InitUnitTurn();*/
	void CreateVictoryWidget();

	void EndBattle();
	void MoveToNextStage();
	void GameOver();
private:
	// Test Var
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> SpawnTestActor;

	// Sequence Var
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	ALevelSequenceActor* LevelSequenceActor;

	// Battle Var
	UPROPERTY(Replicated, meta = (AllowPrivateAccess = true))
	AMyCharacter* CurrentTurnCharacter;

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
		UDataTable* PlayerAnimDataTable;
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

	

	AGameModeBase* GameMode;

	bool bIsBattle;
	//function
};