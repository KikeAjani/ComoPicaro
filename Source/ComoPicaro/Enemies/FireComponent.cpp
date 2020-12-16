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
	PlayShootAnim = false;

	ProjectilePool = NewObject<AProjectilePool>();
	ProjectilePool->Init(3);
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
		PlayShootAnim = true;
	}
}

void UFireComponent::SpawnProjectile()
{
	if (ProjectileClass)
	{
		GetOwner()->GetWorld()->SpawnActor<AProjectile>(ProjectileClass, GetOwner()->GetActorLocation() + SpawnOffset, GetOwner()->GetActorRotation());
	}
}

void UFireComponent::ResetTimeSinceLastShot()
{
	TimeSinceLastShot = 0;
}
