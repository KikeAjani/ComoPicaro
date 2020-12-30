// Fill out your copyright notice in the Description page of Project Settings.


#include "StandingShootingEnemy.h"
#include "Components/FireComponent.h"
#include "Components/LookAtPlayerComponent.h"


// Called when the game starts or when spawned
void AStandingShootingEnemy::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AStandingShootingEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Health <= 0)
	{
		SetDying(true);
		DeactivateLookAtPlayerComponent();
	}

	UFireComponent* FireComponent = Cast<UFireComponent>(GetComponentsByTag(UFireComponent::StaticClass(), "FireComponent")[0]);
	if (FireComponent)
	{
		Shooting = FireComponent->Shooting;
	}

	SetBeaten(Beaten);
}

void AStandingShootingEnemy::SetBeaten(bool _Beaten)
{
	Beaten = (_Beaten && (!Shooting));
}

void AStandingShootingEnemy::SetShooting(bool _Shooting)
{
	UFireComponent* FireComponent = Cast<UFireComponent>(GetComponentsByTag(UFireComponent::StaticClass(), "FireComponent")[0]);
	if (FireComponent)
	{
		FireComponent->Shooting = _Shooting;
	}
}

void AStandingShootingEnemy::Fire()
{
	UFireComponent* FireComponent = Cast<UFireComponent>(GetComponentsByTag(UFireComponent::StaticClass(), "FireComponent")[0]);
	if (FireComponent)
	{
		FireComponent->SpawnProjectile();
	}
}

void AStandingShootingEnemy::DeactivateLookAtPlayerComponent()
{
	ULookAtPlayerComponent* LookAtPlayerComponent = Cast<ULookAtPlayerComponent>(GetComponentsByTag(ULookAtPlayerComponent::StaticClass(), "LookAtPlayerComponent")[0]);
	if (LookAtPlayerComponent)
	{
		LookAtPlayerComponent->Active = false;
	}
}
