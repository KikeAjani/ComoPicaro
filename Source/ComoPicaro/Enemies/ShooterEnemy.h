// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ShooterEnemy.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API AShooterEnemy : public AEnemy
{
	GENERATED_BODY()
		
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootRate;

protected:
	UPROPERTY()
		float TimeSinceLastShot;

public:
	AShooterEnemy();

	virtual void Update(float DeltaTime) override;

protected:
	UFUNCTION()
		virtual void Shoot();

private:
	void ResetTimeSinceLastShot();
};
