// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "WalkingEnemy.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API AWalkingEnemy : public AEnemy
{
	GENERATED_BODY()

public:
	AWalkingEnemy();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Speed;

public:
	virtual void Update(float DeltaTime) override;

protected:
	UFUNCTION()
		virtual void Move(float DeltaTime);

};
