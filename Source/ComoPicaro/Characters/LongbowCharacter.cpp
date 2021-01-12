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
	TArray<UFireComponent*> FireComps;
	GetComponents(FireComps);
	for (UFireComponent* FireComponent: FireComps)
	{
		if(FireComponent->ComponentHasTag("FireComponent")) {
			FireComponent->SpawnProjectile(ExtraDamageSimpleAttack);

		}
	}
}

void ALongbowCharacter::StartDeathAnimation()
{
	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	ULongbowAnimationInstance* LongbowAnim = Cast<ULongbowAnimationInstance>(AnimInstance);
	LongbowAnim->IsDead = true;
}

void ALongbowCharacter::MUltimate_Implementation() {

}

void ALongbowCharacter::BeginPlay() {
	Super::BeginPlay();
}