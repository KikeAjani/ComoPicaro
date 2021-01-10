// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/TargetPoint.h"
#include <ComoPicaro\Enemies\Enemy.h>
#include "TileLevelScriptActor.generated.h"

/**
 *
 */
UCLASS()
class COMOPICARO_API ATileLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		ATargetPoint* SpawnTargetPoint;

	UPROPERTY()
		bool HasEnemySpawned = false;

	UFUNCTION()
		AEnemy* SpawnEnemy(TSubclassOf<AEnemy> enemyClass);
};