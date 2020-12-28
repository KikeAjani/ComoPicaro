// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "StandingShootingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API AStandingShootingEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		bool Shooting;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	virtual void SetBeaten(bool _Beaten) override;

	UFUNCTION(BlueprintCallable)
		void SetShooting(bool _Shooting);

	UFUNCTION(BlueprintCallable)
		void Fire();

protected:
	void DeactivateLookAtPlayerComponent();

};
