// Fill out your copyright notice in the Description page of Project Settings.


#include "TileLevelScriptActor.h"

AEnemy* ATileLevelScriptActor::SpawnEnemy(TSubclassOf<AEnemy> enemyClass, UWorld* world)
{
	AActor* enemyActor = GetWorld()->SpawnActorAbsolute(enemyClass, SpawnTargetPoint->GetActorTransform());
	AEnemy* enemy = static_cast<AEnemy*>(enemyActor);
	return enemy;
}
