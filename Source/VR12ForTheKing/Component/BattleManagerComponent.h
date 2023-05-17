// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "BattleManagerComponent.generated.h"


class AMyCharacter;
UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
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

private:
	// Battle Var
	TArray<TSubclassOf<AMyCharacter>> EnemyClassArray;
	TArray<AMyCharacter*> PlayerCharacterArray;

	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	int32 CurrentBattleRound;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> BattleTurnArray;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TArray<AMyCharacter*> UseBattleTurnArray;
};