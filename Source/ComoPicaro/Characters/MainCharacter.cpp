// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/CapsuleComponent.h"
#include "../ComoPicaroGameInstance.h"

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


	MFireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("FireComponent"));
	UltimateFireComponent = CreateDefaultSubobject<UFireComponent>(TEXT("UltimateFireComponent"));
	IsDead = false;

	PointsToUltimate = 0;
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	ActualHealth = Health;

	TimeSinceLastSimpleAttack = 10000.0f; //Big float to ensure that player can shoot when starts the game
	
	APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PC->SetViewTargetWithBlend(this);
	PC->Possess(this);
	PC->bShowMouseCursor = true;
}

void AMainCharacter::SimpleShoot()
{
	UE_LOG(LogTemp, Warning, TEXT("SimpleShoot is not implemented in child class"));
}

void AMainCharacter::MUltimate()
{
	UE_LOG(LogTemp, Warning, TEXT("Ultimate is not implemented in child class"));
}

// Called every frame
void AMainCharacter::Tick(float DeltaSeconds)
{
 	Super::Tick(DeltaSeconds);

	TimeSinceLastSimpleAttack += DeltaSeconds;
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Set up "movement" bindings.
	PlayerInputComponent->BindAxis("MoveForward", this, &AMainCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AMainCharacter::MoveRight);

	PlayerInputComponent->BindAction("SimpleAttack", IE_Pressed, this, &AMainCharacter::OnSimpleAttack);
	PlayerInputComponent->BindAction("Ultimate", IE_Pressed, this, &AMainCharacter::OnUltimate);
	PlayerInputComponent->BindAction("DisableAA", IE_Released, this, &AMainCharacter::DisableLeftClickPressed);

}


void AMainCharacter::MoveForward(float Value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::MoveRight(float Value)
{
	// Find out which way is "right" and record that the player wants to move that way.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

void AMainCharacter::Damage(int32 Dmg)
{
	ActualHealth -= Dmg;
	if (ActualHealth <= 0) {
		IsDead = true;
		StartDeathAnimation();
	}
}

void AMainCharacter::StartDeathAnimation()
{
	UE_LOG(LogTemp, Warning, TEXT("Death Animation not implemented in this Character"))
}

void AMainCharacter::DisableLeftClickPressed()
{
	IsLeftClickPressed = false;
}



void AMainCharacter::OnSimpleAttack() {
	IsLeftClickPressed = true;
	if (GEngine && TimeSinceLastSimpleAttack>=(1.0f/float(SimpleAttackSpeed)))
	{
		FLatentActionInfo info = FLatentActionInfo();
		info.CallbackTarget = this;
		info.UUID = 0;
		info.Linkage = 1;
		info.ExecutionFunction = FName("SimpleShoot");

		RotationToAttack(info);
		
		TimeSinceLastSimpleAttack = 0;
	}

}


void AMainCharacter::RotationToAttack(FLatentActionInfo info)
{
	ACharacter* PCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);

	FRotator ActorRotation = PCharacter->GetActorRotation();

	FHitResult HitResult;

	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);

	FVector ActorLocation = PCharacter->GetActorLocation();
	FRotator LookAtRotation = UKismetMathLibrary::FindLookAtRotation(ActorLocation, HitResult.Location);

	FRotator NewRotation = FRotator(ActorRotation.Pitch, LookAtRotation.Yaw, ActorRotation.Roll);

	UKismetSystemLibrary::MoveComponentTo(GetCapsuleComponent(), ActorLocation, NewRotation, true, true, 0.08, true, EMoveComponentAction::Move, info);
	//When MoveComponentTo finishes rotation, it will execute SimpleShoot() of Child Class

}


void AMainCharacter::OnUltimate()
{
	if (PointsToUltimate >= 100) {
		FLatentActionInfo info = FLatentActionInfo();
		info.CallbackTarget = this;
		info.UUID = 0;
		info.Linkage = 1;
		info.ExecutionFunction = FName("MUltimate");
		RotationToAttack(info);
		PointsToUltimate = 0;
	}
}

void AMainCharacter::AddHability(APowerUp* PwUp)
{
	UGameInstance *GI= UGameplayStatics::GetGameInstance(this);
	UComoPicaroGameInstance *ComoPicaroGI =  Cast<UComoPicaroGameInstance>(GI);

 	ComoPicaroGI->PlayerListPowerUp.Add(PwUp);
	
}
