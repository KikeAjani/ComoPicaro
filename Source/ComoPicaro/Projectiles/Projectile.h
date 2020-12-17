// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <Components/SphereComponent.h>
#include "Projectile.generated.h"

UCLASS()
class COMOPICARO_API AProjectile : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float SphereCollisionRadius;

	UPROPERTY(EditAnywhere)
		USphereComponent* SphereComponent;

public:
	// Sets default values for this pawn's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
