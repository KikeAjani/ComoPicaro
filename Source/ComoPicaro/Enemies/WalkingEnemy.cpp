// Fill out your copyright notice in the Description page of Project Settings.


#include "WalkingEnemy.h"


AWalkingEnemy::AWalkingEnemy()
{

}

void AWalkingEnemy::Update(float DeltaTime)
{
	Move(DeltaTime);
}

void AWalkingEnemy::Move(float DeltaTime)
{
	SetActorLocation(GetActorLocation() + (GetActorForwardVector() * (Speed * DeltaTime)));
}
