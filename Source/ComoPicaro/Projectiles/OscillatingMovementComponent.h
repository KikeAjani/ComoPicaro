// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OscillatingMovementComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMOPICARO_API UOscillatingMovementComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ForwardSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float OscillationAmplitude;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UCurveFloat* OscillationCurve;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed;

private:
	FVector Direction;
	FVector OscillationDirection;
	float CurveTime;
	float CurveDuration;

public:	
	// Sets default values for this component's properties
	UOscillatingMovementComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
