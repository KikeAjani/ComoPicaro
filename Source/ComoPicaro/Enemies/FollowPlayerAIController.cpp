// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowPlayerAIController.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"


AFollowPlayerAIController::AFollowPlayerAIController()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Active = true;
	MaxSpeed = 0;
}

// Called when the game starts or when spawned
void AFollowPlayerAIController::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFollowPlayerAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active)
	{
		MoveToLocation(UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation());
	}
}

void AFollowPlayerAIController::Deactivate()
{
	Active = false;
	SetCharacterMovementComponentSpeed(0);
}

void AFollowPlayerAIController::Activate()
{
	Active = true;
	SetCharacterMovementComponentSpeed(MaxSpeed);
}

void AFollowPlayerAIController::SetCharacterMovementComponentSpeed(float Speed)
{
	UCharacterMovementComponent* CharacterMovementComponent = Cast<UCharacterMovementComponent>(GetPawn()->GetComponentsByTag(UCharacterMovementComponent::StaticClass(), "CharacterMovementComponent")[0]);
	if (CharacterMovementComponent)
	{
		CharacterMovementComponent->MaxWalkSpeed = Speed;
	}
}
