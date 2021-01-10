// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerUp.h"

// Sets default values
APowerUp::APowerUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
// 	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box"));
// 	BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &APowerUp::OnBoxBeginOverlap);
}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APowerUp::DelegateBroadcast()
{
	PowerUpPickedDelegate.Broadcast();
}

// void APowerUp::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
// {
// 	UE_LOG(LogTemp, Warning, TEXT("New overlap"));
// 	
// }

