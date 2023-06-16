// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class VR12FORTHEKING_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
	
	
protected:
	virtual void CopyProperties(APlayerState* PlayerState);

public:
	// Getter / Setter
	int32 GetTestInt() const;
private:
	UPROPERTY(EditInstanceOnly, meta = (AllowPrivateAccess = true))
	int32 TestInt;
};
