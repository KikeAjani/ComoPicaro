// Fill out your copyright notice in the Description page of Project Settings.


#include "ProjectilePool.h"


AProjectilePool::AProjectilePool() 
{

}

void AProjectilePool::Init(int n)
{
	for (int i = 0; i < n; ++i)
	{
		Objects.Enqueue(NewObject<AProjectile>());
	}
	//Objects = TArray(n);
	//objectPools.Add(typeof(TGenericParam), new ObjectPool<TGeneric<TGenericParam>>(() = > Activator.CreateInstance(typeof(TGeneric<TGenericParam>)) as TGeneric<TGenericParam>));
}

void AProjectilePool::Spawn(FTransform Transform)
{
	AProjectile* Projectile;
	if (Objects.IsEmpty())
	{
		Projectile = NewObject<AProjectile>();
	}
	else
	{
		Objects.Dequeue(Projectile);
	}
	Projectile->SetActorTransform(Transform);
	Projectile->SetActorHiddenInGame(false);
	//Projectile->GetComponent SetVisibility(false);
}

void AProjectilePool::Release(AProjectile* Object)
{
	Object->SetActorHiddenInGame(true);
	Objects.Enqueue(Object);
}