// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/LevelStreaming.h"
#include "MapGenerationLevelScriptActor.generated.h"

/**
 *
 */
UCLASS()
class COMOPICARO_API AMapGenerationLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 GridSize = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TileSize = 1000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 NumOfTilesCreated = 5;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void GenerateRoom();

};
