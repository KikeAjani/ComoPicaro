// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ConstantRotationComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class COMOPICARO_API UConstantRotationComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float MaxRotationSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RotationSpeed;

protected:
	float DecelerationSpeed;
	float AcelerationSpeed;

public:	
	// Sets default values for this component's properties
	UConstantRotationComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
		void SetDeceleration(float Speed);

	UFUNCTION(BlueprintCallable)
		void SetAceleration(float Speed);
		
};
