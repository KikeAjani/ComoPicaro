// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "WarrokBoss.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API AWarrokBoss : public AEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Movements;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MovementWait;

protected:
	FVector TargetLocation;

	int32 CurrentMovement;
	float TimeToNextMovement;
	bool Waiting;

	float TimeShooting;
	bool Shooting;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void ResetTimeToNextMovement();

	void ResetTimeShooting();

	void ResetCurrentMovement();

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
		void SetShooting(bool _Shooting);

};
