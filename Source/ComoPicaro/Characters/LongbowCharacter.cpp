// Fill out your copyright notice in the Description page of Project Settings.


#include "LongbowCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SkeletalMeshComponent.h"
#include "LongbowAnimationInstance.h"
void ALongbowCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
}

void ALongbowCharacter::OnSimpleAttack()
{
	Super::OnSimpleAttack();
	//When Super method finishes and MoveComponentTo rotates, will execute SimpleShoot()
 }

void ALongbowCharacter::OnUltimate()
{
	Super::OnUltimate();
	//When Super method finishes and MoveComponentTo rotates, will execute Ultimate()
}

void ALongbowCharacter::SimpleShoot()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	ULongbowAnimationInstance* LongbowAnim = Cast<ULongbowAnimationInstance>(AnimInstance);
	LongbowAnim->IsShooting = true;
	//MFireComponent->SpawnProjectile(ExtraDamageSimpleAttack);
	TArray<UFireComponent*> FireComps;
	GetComponents(FireComps);
	for (UFireComponent* FireComponent: FireComps)
	{
		if(FireComponent->ComponentHasTag("FireComponent")) {
			FireComponent->SpawnProjectile(ExtraDamageSimpleAttack);

		}
		//UE_LOG(LogTemp, Warning, TEXT("%0.3f %0.3f %0.3f"), FireComponent->SpawnOffset.X, FireComponent->SpawnOffset.Y, FireComponent->SpawnOffset.Z)
	}
	//LongbowAnim->IsShooting = false;
}

void ALongbowCharacter::StartDeathAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	ULongbowAnimationInstance* LongbowAnim = Cast<ULongbowAnimationInstance>(AnimInstance);
	LongbowAnim->IsDead = true;
}

void ALongbowCharacter::MUltimate_Implementation() {
// 	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
// 	ULongbowAnimationInstance* LongbowAnim = Cast<ULongbowAnimationInstance>(AnimInstance);
// 	LongbowAnim->IsUltimating = true;
// 
// 	FHitResult HitResult;
// 
// 	APlayerController* PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
// 	PController->GetHitResultUnderCursorByChannel(UEngineTypes::ConvertToTraceType(ECC_Visibility), true, HitResult);
// 	
// 	ACharacter* PCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
// 	FVector TossVelocity;
// 
// 	const FCollisionResponseParams ResponseParam;
// 	const TArray<AActor*> Actors;
// 	UGameplayStatics::SuggestProjectileVelocity(this, TossVelocity, PCharacter->GetActorLocation(), FVector(0, HitResult.Location.Y, HitResult.Location.Z), 10, false, 5.0f, 0, ESuggestProjVelocityTraceOption::TraceFullPath, ResponseParam, Actors, true);
// 
// 	UltimateFireComponent->SpawnProjectile(0.0f);
	UE_LOG(LogTemp, Warning, TEXT("A"));
}

void ALongbowCharacter::BeginPlay() {
	Super::BeginPlay();
}