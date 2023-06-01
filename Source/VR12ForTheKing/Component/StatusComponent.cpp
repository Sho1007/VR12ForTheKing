// Fill out your copyright notice in the Description page of Project Settings.


#include "../Component/StatusComponent.h"

// Sets default values for this component's properties
UStatusComponent::UStatusComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UStatusComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UStatusComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

int32 UStatusComponent::GetArmor() const
{
	return CharacterStatus.Armor;
}

void UStatusComponent::SetArmor(int32 NewArmor)
{
	CharacterStatus.Armor = NewArmor;
	if (UpdateArmor.IsBound())
	{
		UpdateArmor.Execute(CharacterStatus.Armor);
	}
}

int32 UStatusComponent::GetCognition() const
{
	return CharacterStatus.Cognition;
}

void UStatusComponent::SetCognition(int32 NewCognition)
{
	CharacterStatus.Cognition = NewCognition;
	if (UpdateCognition.IsBound())
	{
		UpdateCognition.Execute(CharacterStatus.Cognition);
	}
}

int32 UStatusComponent::GetEvasion() const
{
	return CharacterStatus.Evasion;
}

void UStatusComponent::SetEvasion(int32 NewEvasion)
{
	CharacterStatus.Evasion = NewEvasion;

	if (UpdateEvasion.IsBound())
	{
		UpdateEvasion.Execute(CharacterStatus.Evasion);
	}
}

int32 UStatusComponent::GetIntelligence() const
{
	return CharacterStatus.Intelligence;
}

void UStatusComponent::SetIntelligence(int32 NewIntelligence)
{
	CharacterStatus.Intelligence = NewIntelligence;
	if (UpdateIntelligence.IsBound())
	{
		UpdateIntelligence.Execute(CharacterStatus.Intelligence);
	}
}

int32 UStatusComponent::GetLuck() const
{
	return CharacterStatus.Luck;
}

void UStatusComponent::SetLuck(int32 NewLuck)
{
	CharacterStatus.Luck = NewLuck;
	if (UpdateLuck.IsBound())
	{
		UpdateLuck.Execute(CharacterStatus.Luck);
	}
}

int32 UStatusComponent::GetResistance() const
{
	return CharacterStatus.Resistance;
}

void UStatusComponent::SetResistance(int32 NewResistance)
{
	CharacterStatus.Resistance = NewResistance;
	if (UpdateResistance.IsBound())
	{
		UpdateResistance.Execute(CharacterStatus.Resistance);
	}
}

int32 UStatusComponent::GetSpeed() const
{
	return CharacterStatus.Speed;
}

void UStatusComponent::SetSpeed(int32 NewSpeed)
{
	CharacterStatus.Speed = NewSpeed;
	if (UpdateSpeed.IsBound())
	{
		UpdateSpeed.Execute(CharacterStatus.Speed);
	}
}

int32 UStatusComponent::GetStrength() const
{
	return CharacterStatus.Strength;
}

void UStatusComponent::SetStrength(int32 NewStrength)
{
	CharacterStatus.Strength = NewStrength;
	if (UpdateStrength.IsBound())
	{
		UpdateStrength.Execute(CharacterStatus.Strength);
	}
}

int32 UStatusComponent::GetTalent() const
{
	return CharacterStatus.Talent;
}

void UStatusComponent::SetTalent(int32 NewTalent)
{
	CharacterStatus.Talent = NewTalent;
	if (UpdateTalent.IsBound())
	{
		UpdateTalent.Execute(CharacterStatus.Talent);
	}
}

int32 UStatusComponent::GetVitality() const
{
	return CharacterStatus.Vitality;
}

void UStatusComponent::SetVitality(int32 NewVitality)
{
	CharacterStatus.Vitality = NewVitality;
	if (UpdateVitality.IsBound())
	{
		UpdateVitality.Execute(CharacterStatus.Vitality);
	}
}

int32 UStatusComponent::GetCurrentHP() const
{
	return CharacterStatus.CurrentHP;
}

void UStatusComponent::SetCurrentHP(int32 NewCurrentHP)
{
	CharacterStatus.CurrentHP = NewCurrentHP;
	if (UpdateCurrentHP.IsBound())
	{
		UpdateCurrentHP.Execute(CharacterStatus.CurrentHP);
	}
}

int32 UStatusComponent::GetMaxHP() const
{
	return CharacterStatus.MaxHP;
}

void UStatusComponent::SetMaxHP(int32 NewMaxHP)
{
	CharacterStatus.MaxHP = NewMaxHP;
	if (UpdateMaxHP.IsBound())
	{
		UpdateMaxHP.Execute(CharacterStatus.MaxHP);
	}
}

int32 UStatusComponent::GetCurrentExP() const
{
	return CharacterStatus.CurrentExP;
}

void UStatusComponent::SetCurrentExP(int32 NewCurrentExP)
{
	CharacterStatus.CurrentExP = NewCurrentExP;
	if (UpdateCurrentExP.IsBound())
	{
		UpdateCurrentExP.Execute(CharacterStatus.CurrentExP);
	}
}

int32 UStatusComponent::GetMaxExP() const
{
	return CharacterStatus.MaxExP;
}

void UStatusComponent::SetMaxExP(int32 NewMaxExP)
{
	CharacterStatus.MaxExP = NewMaxExP;
	if (UpdateMaxExP.IsBound())
	{
		UpdateMaxExP.Execute(CharacterStatus.MaxExP);
	}
}

int32 UStatusComponent::GetCurrentFocus() const
{
	return CharacterStatus.CurrentFocus;
}

void UStatusComponent::SetCurrentFocus(int32 NewCurrentFocus)
{
	CharacterStatus.CurrentFocus = NewCurrentFocus;
	if (UpdateCurrentFocus.IsBound())
	{
		UpdateCurrentFocus.Execute(CharacterStatus.CurrentFocus);
	}
}

int32 UStatusComponent::GetMaxFocus() const
{
	return CharacterStatus.MaxFocus;
}

void UStatusComponent::SetMaxFocus(int32 NewMaxFocus)
{
	CharacterStatus.MaxFocus = NewMaxFocus;
	if (UpdateMaxFocus.IsBound())
	{
		UpdateMaxFocus.Execute(CharacterStatus.MaxFocus);
	}
}

int32 UStatusComponent::GetAttackPower() const
{
	return CharacterStatus.AttackPower;
}

void UStatusComponent::SetAttackPower(int32 NewAttackPower)
{
	CharacterStatus.AttackPower = NewAttackPower;
	if (UpdateAttackPower.IsBound())
	{
		UpdateAttackPower.Execute(CharacterStatus.AttackPower);
	}
}

bool UStatusComponent::IsMagicalAttackPower() const
{
	return CharacterStatus.bIsMagicalAttackPower;
}

void UStatusComponent::SetIsMagicalAttackPower(bool NewIsMagicalAttackPower)
{
	CharacterStatus.bIsMagicalAttackPower = NewIsMagicalAttackPower;
	if (UpdateIsMagicalAttackPower.IsBound())
	{
		UpdateIsMagicalAttackPower.Execute(CharacterStatus.bIsMagicalAttackPower);
	}
}

int32 UStatusComponent::GetLevel() const
{
	return CharacterStatus.Level;
}

void UStatusComponent::SetLevel(int32 NewLevel)
{
	CharacterStatus.Level = NewLevel;
	if (UpdateLevel.IsBound())
	{
		UpdateLevel.Execute(CharacterStatus.Level);
	}
}
