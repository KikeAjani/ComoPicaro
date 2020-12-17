// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Projectiles/Projectile.h"
#include "Components/ActorComponent.h"
#include "FireComponent.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class COMOPICARO_API UFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float ShootRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FVector SpawnOffset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<AProjectile> ProjectileClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool PlayShootAnim;

protected:
	UPROPERTY()
		float TimeSinceLastShot;

public:
	// Sets default values for this component's properties
	UFireComponent();

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
