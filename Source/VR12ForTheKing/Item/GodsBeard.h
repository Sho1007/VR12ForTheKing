// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Item/ItemBase.h"
#include "GodsBeard.generated.h"

/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AGodsBeard : public AItemBase
{
	GENERATED_BODY()
	
public:
	virtual void Use(AMyCharacter* OwnerCharacter) override;
};
