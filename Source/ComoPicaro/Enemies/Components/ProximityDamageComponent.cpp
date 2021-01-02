// Fill out your copyright notice in the Description page of Project Settings.


#include "ProximityDamageComponent.h"
#include "../../Characters/MainCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values for this component's properties
UProximityDamageComponent::UProximityDamageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UProximityDamageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UProximityDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TimeSinceLastDamage += DeltaTime;
	if (TimeAbleToDamage() && DistanceAbleToDamage())
	{
		ResetTimeSinceLastAttack();
		AMainCharacter* MainCharacter = Cast<AMainCharacter>(GetTarget());
		if (MainCharacter)
		{
			MainCharacter->Damage(Damage);
			UE_LOG(LogTemp, Warning, TEXT("proximity damage %0.3f"), MainCharacter->Health);
		}
	}
}

bool UProximityDamageComponent::TimeAbleToDamage()
{
	return (TimeSinceLastDamage > DamageRate);
}

bool UProximityDamageComponent::DistanceAbleToDamage()
{
	return (GetOwner()->GetDistanceTo(GetTarget()) < DamageRange);
}

APawn* UProximityDamageComponent::GetTarget()
{
	return UGameplayStatics::GetPlayerPawn(this, 0);
}

void UProximityDamageComponent::ResetTimeSinceLastAttack()
{
	TimeSinceLastDamage = 0;
}
