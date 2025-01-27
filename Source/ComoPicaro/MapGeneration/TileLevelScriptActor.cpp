// Fill out your copyright notice in the Description page of Project Settings.


#include "TileLevelScriptActor.h"

AEnemy* ATileLevelScriptActor::SpawnEnemy(TSubclassOf<AEnemy> enemyClass)
{
	FTransform spawnTransform = SpawnTargetPoint->GetTransform();

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AActor* enemyActor = GetWorld()->SpawnActorAbsolute(enemyClass, spawnTransform, spawnParams);
	AEnemy* enemy = static_cast<AEnemy*>(enemyActor);

	AEnemy* defaultEnemy = static_cast<AEnemy*>(enemyClass->GetDefaultObject());
	FVector defaultScale = defaultEnemy->GetActorScale();
	enemy->SetActorScale3D(defaultScale);

	FVector originalLocation = enemy->GetActorLocation();
	FVector boundOrigin;
	FVector boundExtent;
	enemy->GetActorBounds(false, boundOrigin, boundExtent);
	float enemyHeight = boundExtent.Z - boundOrigin.Z;
	originalLocation.Z += enemyHeight;
	enemy->SetActorLocation(originalLocation);

	HasEnemySpawned = true;

	return enemy;
}
