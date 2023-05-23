// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BattleMap.generated.h"

USTRUCT(BlueprintType)
struct FBattleSceneInfo
{
	GENERATED_BODY()
	
	FBattleSceneInfo()
	{
		PlayerSpawnPosition.Init(nullptr, 3);
		EnemySpawnPosition.Init(nullptr, 3);
	}
	
	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<AActor*> PlayerSpawnPosition;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	TArray<AActor*> EnemySpawnPosition;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	AActor* PlayerSideCamera;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	AActor* NeutralSideCamera;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly)
	AActor* EnemySideCamera;
};

UCLASS()
class VR12FORTHEKING_API ABattleMap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABattleMap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Getter / Setter
	const TArray<AActor*>& GetEnemySpawnPosition() const;
	const TArray<AActor*>& GetPlayerSpawnPosition() const;

	UFUNCTION(BlueprintCallable)
	const AActor* GetPlayerSideCamera() const;
	UFUNCTION(BlueprintCallable)
	const AActor* GetEnemySideCamera() const;
	UFUNCTION(BlueprintCallable)
	const AActor* GetNeutralSideCamera() const;
	UFUNCTION(BlueprintCallable)
	const AActor* GetNextNeutralSideCamera() const;

	UFUNCTION(BlueprintCallable)
	const int32 GetLastSceneIndex() const;
	UFUNCTION(BlueprintCallable)
	const int32 GetCurrentSceneIndex() const;
	UFUNCTION(BlueprintCallable)
	const bool IsLastScene() const;
	UFUNCTION(BlueprintCallable)
	const bool MoveNextSceneIndex();
private:
	int32 CurrentSceneIndex = 0;

	UPROPERTY(BlueprintReadOnly, EditInstanceOnly, meta = (AllowPrivateAccess = true))
	TArray<FBattleSceneInfo> BattleSceneInfoArray;
};
