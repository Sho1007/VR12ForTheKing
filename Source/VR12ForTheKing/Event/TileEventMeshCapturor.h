// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TileEventMeshCapturor.generated.h"


class USceneCaptureComponent2D;
class AEventActor;
UCLASS()
class VR12FORTHEKING_API ATileEventMeshCapturor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileEventMeshCapturor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void SetFocusTarget(AEventActor* NewTargetActor);
private:
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	USceneCaptureComponent2D* SceneCaptureComponent;
};
