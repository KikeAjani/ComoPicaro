// Fill out your copyright notice in the Description page of Project Settings.


#include "LongbowCharacter.h"
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

void ALongbowCharacter::SimpleShoot()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	ULongbowAnimationInstance* LongbowAnim = Cast<ULongbowAnimationInstance>(AnimInstance);
	LongbowAnim->IsShooting = true;
	MFireComponent->SpawnProjectile();
	//LongbowAnim->IsShooting = false;
}

void ALongbowCharacter::BeginPlay() {
	Super::BeginPlay();
}