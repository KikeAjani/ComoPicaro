// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "LongbowAnimationInstance.generated.h"

/**
 *
 */
UCLASS()
class COMOPICARO_API ULongbowAnimationInstance : public UAnimInstance
{
	GENERATED_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsRunning;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsShooting;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsUltimating;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool IsDead;
};
