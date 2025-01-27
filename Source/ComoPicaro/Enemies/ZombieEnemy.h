// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "ZombieEnemy.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API AZombieEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly)
		float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxSpeed;

	UPROPERTY(BlueprintReadOnly)
		bool Attacking;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetBeaten(bool _Beaten) override;

	UFUNCTION(BlueprintCallable)
		void SetAttacking(bool _Attacking);

	UFUNCTION(BlueprintCallable)
		void Hit();

protected:
	void SetAIActive(bool Active);

	void SetCharacterMovementComponentSpeed(float Speed);

};
