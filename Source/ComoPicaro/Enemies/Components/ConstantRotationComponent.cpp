// Fill out your copyright notice in the Description page of Project Settings.


#include "ConstantRotationComponent.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values for this component's properties
UConstantRotationComponent::UConstantRotationComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	DecelerationSpeed = 0;
	AcelerationSpeed = 0;
}


// Called when the game starts
void UConstantRotationComponent::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UConstantRotationComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FRotator Rotator = FRotator::ZeroRotator;
	Rotator.Yaw = RotationSpeed * DeltaTime;
	GetOwner()->AddActorLocalRotation(Rotator);

	if (DecelerationSpeed > 0)
	{
		if (RotationSpeed > 0)
		{
			RotationSpeed = FMath::Max(0.0f, RotationSpeed - (DecelerationSpeed * DeltaTime));
		}
		else
		{
			DecelerationSpeed = 0;
		}
	}
	else if (AcelerationSpeed > 0)
	{
		if (RotationSpeed < MaxRotationSpeed)
		{
			RotationSpeed = FMath::Max(MaxRotationSpeed, RotationSpeed + (AcelerationSpeed * DeltaTime));
		}
		else
		{
			AcelerationSpeed = 0;
		}
	}
}

void UConstantRotationComponent::SetDeceleration(float Speed)
{
	DecelerationSpeed = Speed;
}

void UConstantRotationComponent::SetAceleration(float Speed)
{
	AcelerationSpeed = Speed;
}
