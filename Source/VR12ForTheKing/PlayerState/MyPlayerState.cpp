// Fill out your copyright notice in the Description page of Project Settings.


#include "../PlayerState/MyPlayerState.h"

void AMyPlayerState::CopyProperties(APlayerState* PlayerState)
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 60, FColor::Cyan, FString::Printf(TEXT("CopyProperties Called")));
	Super::CopyProperties(PlayerState);

	if (AMyPlayerState* MyPlateState = Cast<AMyPlayerState>(PlayerState))
	{
		TestInt = MyPlateState->GetTestInt();
	}
}

int32 AMyPlayerState::GetTestInt() const
{
	return TestInt;
}
