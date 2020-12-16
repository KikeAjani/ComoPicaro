// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterEnemy.h"


AShooterEnemy::AShooterEnemy()
{
	ResetTimeSinceLastShot();
}

void AShooterEnemy::Update(float DeltaTime)
{
	TimeSinceLastShot += DeltaTime;
	if (TimeSinceLastShot > ShootRate)
	{
		ResetTimeSinceLastShot();
		Shoot();
	}
}

void AShooterEnemy::Shoot()
{
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Yellow, TEXT("SHOT!"));
}

void AShooterEnemy::ResetTimeSinceLastShot()
{
	TimeSinceLastShot = 0;
}