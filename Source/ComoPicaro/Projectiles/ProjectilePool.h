// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Containers/Array.h"
#include "Projectile.h"
#include "GameFramework/Actor.h"
#include "ProjectilePool.generated.h"

UCLASS()
class COMOPICARO_API AProjectilePool : public AActor
{
	GENERATED_BODY()

protected:
	TQueue<AProjectile*> Objects;

public:
	AProjectilePool();

	void Init(int n);

	void Spawn(FTransform Transform);

	void Release(AProjectile* Object);
};
