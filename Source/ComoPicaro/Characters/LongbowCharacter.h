// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MainCharacter.h"
#include "LongbowCharacter.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API ALongbowCharacter : public AMainCharacter
{
	GENERATED_BODY()
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	virtual void OnSimpleAttack() override;
	virtual void OnUltimate() override;

	//UFUNCTION(BlueprintCallable)
	virtual void SimpleShoot() override;

	UFUNCTION(BlueprintNativeEvent)
	void MUltimate() override;
	virtual void StartDeathAnimation() override;
};
