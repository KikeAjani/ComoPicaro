// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "../Enemies/Enemy.h"


// Sets default values
AProjectile::AProjectile()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->Damage(Damage);
	}

// 	A* Character = Cast<A>(OtherActor);
// 	if (Character)
// 	{
// 		Character->Damage(Damage);
// 	}

	Destroy();
}
