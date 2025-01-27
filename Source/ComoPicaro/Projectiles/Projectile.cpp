// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "../Enemies/Enemy.h"
#include "../Characters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"

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

void AProjectile::AddExtraDamage(int32 ExtraDmg)
{
	Damage += ExtraDmg;
}


void AProjectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		Enemy->Damage(Damage);
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(UGameplayStatics::GetPlayerCharacter(GetWorld(), 0));
		MainCharacter->PointsToUltimate += 5;


	}
	else
	{
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(OtherActor);
		if (MainCharacter)
		{
			MainCharacter->Damage(Damage);
		}
	}
	Destroy();
}
