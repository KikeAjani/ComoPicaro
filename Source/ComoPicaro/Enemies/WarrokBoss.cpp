// Fill out your copyright notice in the Description page of Project Settings.


#include "WarrokBoss.h"
#include "Kismet/GameplayStatics.h"
#include "Components/FireComponent.h"
#include "Components/ConstantRotationComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


// Called when the game starts or when spawned
void AWarrokBoss::BeginPlay()
{
	Super::BeginPlay();

	SetShooting(false);
	ResetCurrentMovement();
	ResetTimeToNextMovement();
	Waiting = true;

	Active = false;
	Stopping = false;
}

// Called every frame
void AWarrokBoss::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Active)
	{

		if (Health <= 0)
		{
			UConstantRotationComponent* ConstantRotationComponent = Cast<UConstantRotationComponent>(GetComponentsByTag(UConstantRotationComponent::StaticClass(), "ConstantRotationComponent")[0]);
			if (ConstantRotationComponent)
			{
				if (ConstantRotationComponent->RotationSpeed > 0)
				{
					if (!Stopping)
					{
						Stopping = true;
						ConstantRotationComponent->SetDeceleration(ConstantRotationComponent->MaxRotationSpeed * 4);
					}
				}
				else
				{
					SetDying(true);
				}
			}
		}
		else if (Shooting)
		{
			UFireComponent* FireComponent = Cast<UFireComponent>(GetComponentsByTag(UFireComponent::StaticClass(), "FireComponent")[0]);
			if (FireComponent && FireComponent->Shooting)
			{
				FireComponent->SpawnProjectile();
				FireComponent->Shooting = false;
			}
			TimeShooting += DeltaTime;
			if (TimeShooting >= ShootingTime)
			{
				SetShooting(false);
				ResetCurrentMovement();
				ResetTimeToNextMovement();
				Waiting = true;
			}
		}
		else
		{
			if (CurrentMovement > Movements)
			{
				SetShooting(true);
				ResetTimeShooting();
			}

			if (Waiting)
			{
				TimeToNextMovement -= DeltaTime;
				if (TimeToNextMovement <= 0)
				{
					Waiting = false;
					TargetLocation = UGameplayStatics::GetPlayerPawn(this, 0)->GetActorLocation();
					TargetLocation.Z = GetActorLocation().Z;
					CurrentMovement++;
				}
			}
			else
			{
				if (FVector::Distance(GetActorLocation(), TargetLocation) > (Speed / 10))
				{
					FVector Direction = (TargetLocation - GetActorLocation());
					Direction.Normalize();
					SetActorLocation(GetActorLocation() + (Direction * Speed * DeltaTime));
				}
				else
				{
					ResetTimeToNextMovement();
					Waiting = true;
				}
			}
		}

	}
}

void AWarrokBoss::ResetTimeToNextMovement()
{
	TimeToNextMovement = MovementWait;
}

void AWarrokBoss::ResetTimeShooting()
{
	TimeShooting = 0;
}

void AWarrokBoss::ResetCurrentMovement()
{
	CurrentMovement = 0;
}

void AWarrokBoss::SetShooting(bool _Shooting)
{
	Shooting = _Shooting;
}

void AWarrokBoss::Activate()
{
	Active = true;
	if (Health > 0)
	{
		UConstantRotationComponent* ConstantRotationComponent = Cast<UConstantRotationComponent>(GetComponentsByTag(UConstantRotationComponent::StaticClass(), "ConstantRotationComponent")[0]);
		if (ConstantRotationComponent)
		{
			ConstantRotationComponent->SetAceleration(ConstantRotationComponent->MaxRotationSpeed * 2);
		}
	}
}
