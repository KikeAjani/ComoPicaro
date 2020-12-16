// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values for this component's properties
UShootComponent::UShootComponent()
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
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...

}

// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastShot += DeltaTime;
	if (TimeSinceLastShot > ShootRate)
	{
		ResetTimeSinceLastShot();
		PlayShootAnim = true;
	}
}

void UShootComponent::SpawnProjectile()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SHOT!"));
	//ProjectilePool->Spawn(GetOwner()->GetTransform());
}

void UShootComponent::ResetTimeSinceLastShot()
{
	TimeSinceLastShot = 0;
}
