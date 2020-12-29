// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Pawn.h"
#include "ProximityDamageComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMOPICARO_API UProximityDamageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Damage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DamageRange;

protected:
	float TimeSinceLastDamage;

public:	
	// Sets default values for this component's properties
	UProximityDamageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	APawn* GetTarget();

	void ResetTimeSinceLastAttack();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		bool TimeAbleToDamage();

	UFUNCTION(BlueprintCallable)
		bool DistanceAbleToDamage();


};
