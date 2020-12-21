// Fill out your copyright notice in the Description page of Project Settings.


#include "OscillatingMovementComponent.h"

// Sets default values for this component's properties
UOscillatingMovementComponent::UOscillatingMovementComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...

}


// Called when the game starts
void UOscillatingMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	Direction = GetOwner()->GetActorForwardVector();
	OscillationDirection = GetOwner()->GetActorForwardVector().RotateAngleAxis(-90.0f, FVector(0, 0, 1));

	if (OscillationCurve)
	{
		OscillationCurve->GetTimeRange(CurveTime, CurveDuration);
	}
}


// Called every frame
void UOscillatingMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector ForwardAddition = (Direction * ForwardSpeed * DeltaTime);
	if (OscillationCurve)
	{
		CurveTime = fmod(CurveTime + DeltaTime, CurveDuration);
		FVector OscillationAddition = (OscillationDirection * OscillationCurve->GetFloatValue(CurveTime) * OscillationAmplitude);
		GetOwner()->SetActorLocation(GetOwner()->GetActorLocation() + ForwardAddition + OscillationAddition);
	}

	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = RotationSpeed;
	GetOwner()->AddActorLocalRotation(Rotator);
}

