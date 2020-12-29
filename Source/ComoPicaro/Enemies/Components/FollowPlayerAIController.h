// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FollowPlayerAIController.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API AFollowPlayerAIController : public AAIController
{
	GENERATED_BODY()

private:
	bool Active;

public:
	AFollowPlayerAIController();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetActive(bool _Active);

private:
	void SetCharacterMovementComponentSpeed(float Speed);

};