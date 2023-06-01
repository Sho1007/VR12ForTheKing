// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StatusComponent.generated.h"

DECLARE_DELEGATE_OneParam(FDele_Single_Int, int32);
DECLARE_DELEGATE_OneParam(FDele_Single_Bool, bool);

USTRUCT(BlueprintType)
struct FCharacterStatus
{
	GENERATED_BODY()

public:
	// Status
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Armor;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Cognition;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Evasion;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Intelligence;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Luck;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Resistance;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Speed;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Strength;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Talent;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Vitality;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxHP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentExP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxExP;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 CurrentFocus;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxFocus;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 AttackPower;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	bool bIsMagicalAttackPower;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 Level;
};

UCLASS( Blueprintable, ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VR12FORTHEKING_API UStatusComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UStatusComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
public:
	// Getter / Setter
	int32 GetArmor() const;
	void SetArmor(int32 NewArmor);

	int32 GetCognition() const;
	void SetCognition(int32 NewCognition);

	int32 GetEvasion() const;
	void SetEvasion(int32 NewEvasion);

	int32 GetIntelligence() const;
	void SetIntelligence(int32 NewIntelligence);
	
	int32 GetLuck() const;
	void SetLuck(int32 NewLuck);
	
	int32 GetResistance() const;
	void SetResistance(int32 NewResistance);
	
	int32 GetSpeed() const;
	void SetSpeed(int32 NewSpeed);
	
	int32 GetStrength() const;
	void SetStrength(int32 NewStrength);
	
	int32 GetTalent() const;
	void SetTalent(int32 NewTalent);
	
	int32 GetVitality() const;
	void SetVitality(int32 NewVitality);
	
	int32 GetCurrentHP() const;
	void SetCurrentHP(int32 NewCurrentHP);
	
	int32 GetMaxHP() const;
	void SetMaxHP(int32 NewMaxHP);
	
	int32 GetCurrentExP() const;
	void SetCurrentExP(int32 NewCurrentExP);
	
	int32 GetMaxExP() const;
	void SetMaxExP(int32 NewMaxExP);
	
	int32 GetCurrentFocus() const;
	void SetCurrentFocus(int32 NewCurrentFocus);
	
	int32 GetMaxFocus() const;
	void SetMaxFocus(int32 NewMaxFocus);
	
	int32 GetAttackPower() const;
	void SetAttackPower(int32 NewAttackPower);

	bool IsMagicalAttackPower() const;
	void SetIsMagicalAttackPower(bool NewIsMagicalAttackPower);
	
	int32 GetLevel() const;
	void SetLevel(int32 NewLevel);
public:
	// Delegate
	FDele_Single_Int UpdateArmor;
	FDele_Single_Int UpdateCognition;
	FDele_Single_Int UpdateEvasion;
	FDele_Single_Int UpdateIntelligence;
	FDele_Single_Int UpdateLuck;
	FDele_Single_Int UpdateResistance;
	FDele_Single_Int UpdateSpeed;
	FDele_Single_Int UpdateStrength;
	FDele_Single_Int UpdateTalent;
	FDele_Single_Int UpdateVitality;

	FDele_Single_Int UpdateCurrentHP;
	FDele_Single_Int UpdateMaxHP;
	FDele_Single_Int UpdateCurrentExP;
	FDele_Single_Int UpdateMaxExP;
	FDele_Single_Int UpdateCurrentFocus;
	FDele_Single_Int UpdateMaxFocus;

	FDele_Single_Int UpdateAttackPower;
	FDele_Single_Bool UpdateIsMagicalAttackPower;
	FDele_Single_Int UpdateLevel;
private:
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (AllowPrivateAccess =  true))
	FCharacterStatus CharacterStatus;
};