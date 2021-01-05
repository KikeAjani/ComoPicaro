// Fill out your copyright notice in the Description page of Project Settings.


#include "FireComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UFireComponent::UFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ResetTimeSinceLastShot();
	Shooting = false;
}

// Called when the game starts
void UFireComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastShot += DeltaTime;
	if (TimeSinceLastShot > ShootRate)
	{
		ResetTimeSinceLastShot();
		Shooting = true;
	}
}


void UFireComponent::SpawnProjectile(int32 ExtraDamage)
{
	if (ProjectileClass)
	{
		AProjectile* Projectile = GetOwner()->GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetOwner()->GetActorLocation() + GetOwner()->GetActorRotation().RotateVector(SpawnOffset), GetOwner()->GetActorRotation());
		if (Projectile) {
			Projectile->AddExtraDamage(ExtraDamage);
		}
	}
}

void UFireComponent::ResetTimeSinceLastShot()
{
	TimeSinceLastShot = 0;
}
