// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ComoPicaroProjectile.h"
#include "GameFramework/CharacterMovementComponent.h"

const FName AMainCharacter::MoveForwardBinding("MoveForward");
const FName AMainCharacter::MoveRightBinding("MoveRight");
const FName AMainCharacter::FireForwardBinding("FireForward");
const FName AMainCharacter::FireRightBinding("FireRight");

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	// Cache our sound effect
	static ConstructorHelpers::FObjectFinder<USoundBase> FireAudio(TEXT("/Game/TwinStick/Audio/TwinStickFire.TwinStickFire"));
	FireSound = FireAudio.Object;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when ship does
	CameraBoom->TargetArmLength = 1200.f;
	CameraBoom->SetRelativeRotation(FRotator(-80.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	CameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	CameraComponent->bUsePawnControlRotation = false;	// Camera does not rotate relative to arm

		// Movement
	MoveSpeed = 1000.0f;
	// Weapon
	GunOffset = FVector(90.f, 0.f, 0.f);
	FireRate = 0.1f;
	bCanFire = true;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetViewTargetWithBlend(this);
	PC->Possess(this);
}

// Called every frame
void AMainCharacter::Tick(float DeltaSeconds)
{
 	Super::Tick(DeltaSeconds);
// // 		 Find movement direction
// 		const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
// 		const float RightValue = GetInputAxisValue(MoveRightBinding);
// 	
// 		// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
// 		const FVector MoveDirection = FVector(ForwardValue, RightValue, 0.f).GetClampedToMaxSize(1.0f);
// 	
// 		// Calculate  movement
// 		const FVector Movement = MoveDirection * MoveSpeed * DeltaSeconds;
// 	
// 		// If non-zero size, move this actor
// 		float mov = Movement.SizeSquared();
// 		if (Movement.SizeSquared() > 0.0f)
// 		{
// 
// 			const FRotator NewRotation = Movement.Rotation();
// 			lastRotator = NewRotation;
// 	
// 			FHitResult Hit(1.f);
// 	
// 			RootComponent->MoveComponent(Movement, NewRotation, true, &Hit);
// 	
// 
// 			if (Hit.IsValidBlockingHit())
// 			{
// 				const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
// 				const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
// 				RootComponent->MoveComponent(Deflection, NewRotation, true);
// 			}
// 		}
// 	
// 		// Create fire direction vector
// 		const float FireForwardValue = GetInputAxisValue(FireForwardBinding);
// 		const float FireRightValue = GetInputAxisValue(FireRightBinding);
// 		const FVector FireDirection = FVector(FireForwardValue, FireRightValue, 0.f);
// 	
// 		// Try and fire a shot
// 		FireShot(FireDirection);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	//check(PlayerInputComponent);

	// set up gameplay key bindings
// 	PlayerInputComponent->BindAxis(MoveForwardBinding);
// 	PlayerInputComponent->BindAxis(MoveRightBinding);
// 
// 	PlayerInputComponent->BindAxis(FireForwardBinding);
// 	PlayerInputComponent->BindAxis(FireRightBinding);

	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);
}

void AMainCharacter::FireShot(FVector FireDirection)
{
	// If it's ok to fire again
	if (bCanFire == true)
	{
		// If we are pressing fire stick in a direction
		if (FireDirection.SizeSquared() > 0.0f)
		{
			const FRotator FireRotation = FireDirection.Rotation();
			// Spawn projectile at an offset from this pawn
			const FVector SpawnLocation = GetActorLocation() + FireRotation.RotateVector(GunOffset);

			UWorld* const World = GetWorld();
			if (World != NULL)
			{
				// spawn the projectile
				World->SpawnActor<AComoPicaroProjectile>(SpawnLocation, FireRotation);
			}

			bCanFire = false;
			World->GetTimerManager().SetTimer(TimerHandle_ShotTimerExpired, this, &AMainCharacter::ShotTimerExpired, FireRate);

			// try and play the sound if specified
			if (FireSound != nullptr)
			{
				UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
			}

			bCanFire = false;
		}
	}
}

void AMainCharacter::ShotTimerExpired()
{
	bCanFire = true;
}


void AMainCharacter::MoveForward(float Value)
{
// 
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);

}

void AMainCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}
