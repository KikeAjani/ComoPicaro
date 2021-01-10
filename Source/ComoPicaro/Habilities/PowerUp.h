// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PowerUp.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FPowerUpPickedDelegate);


UCLASS(BlueprintType)
class COMOPICARO_API APowerUp : public AActor 
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APowerUp();

	UPROPERTY(BlueprintAssignable)
		FPowerUpPickedDelegate PowerUpPickedDelegate;
// 
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 		class UStaticMeshComponent* StaticMeshPowerUp;
// 
// 	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
// 		class UBoxComponent* BoxComponent;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void DelegateBroadcast();
	
// 	UFUNCTION()
// 	void OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
