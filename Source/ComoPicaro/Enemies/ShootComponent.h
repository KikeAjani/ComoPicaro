// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectiles/Projectile.h"
#include "../Projectiles/ProjectilePool.h"
#include "Components/ActorComponent.h"
#include "ShootComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMOPICARO_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayShootAnim;

protected:
	UPROPERTY()
		float TimeSinceLastShot;

	UPROPERTY()
		AProjectilePool* ProjectilePool;

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:
	UFUNCTION(BlueprintCallable)
		void SpawnProjectile();

private:
	void ResetTimeSinceLastShot();
		
};
