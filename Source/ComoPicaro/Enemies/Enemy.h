// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Enemy.generated.h"

UCLASS()
class COMOPICARO_API AEnemy : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Dificulty;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		bool Beaten;

private:
	bool Dying;

public:
	// Sets default values for this pawn's properties
	AEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
		void Damage(int Damage);

	UFUNCTION(BlueprintCallable, BlueprintImplementableEvent)
		void Die();

};
