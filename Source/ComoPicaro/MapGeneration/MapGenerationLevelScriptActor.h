// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "Engine/LevelStreaming.h"
#include <ComoPicaro\MapGeneration\TileLevelScriptActor.h>
#include <ComoPicaro\Habilities\PowerUp.h>
#include <ComoPicaro\ComoPicaroGameInstance.h>
#include "MapGenerationLevelScriptActor.generated.h"

USTRUCT()
struct FTileArray {
	GENERATED_BODY()
public:

	TArray<ULevelStreaming*> TileArray;

	ULevelStreaming* operator[] (int32 i) {
		return TileArray[i];
	}

	void Add(ULevelStreaming* tile) {
		TileArray.Add(tile);
	}

	void Insert(ULevelStreaming* tile, int32 index) {
		TileArray.Insert(tile, index);
	}
};

/**
 *
 */
UCLASS()
class COMOPICARO_API AMapGenerationLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

private:
	int32 TilesLoaded = 0;

	float GridCenter;

	int32 EnemyNum = 0;

public:
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 GridSize = 4;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float TileSize = 1000;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		int32 NumOfTileTypes = 5;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<AEnemy>> EnemyTypes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TArray<TSubclassOf<APowerUp>> PowerUpTypes;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		TSubclassOf<class AActor> EndLevelPortalType;

	UPROPERTY()
		TArray<FTileArray> TileGrid;

private:
	UFUNCTION()
		void OnTileLoaded();

	void OnAllTilesLoaded();

public:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void GenerateRoom();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		ATileLevelScriptActor* GetRandomTileScriptActor();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void SpawnEnemies();

	UFUNCTION()
		void EnemyDeath();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void SpawnRandomPowerUp();

	UFUNCTION(BlueprintCallable, Category = LevelBlueprint)
		void SpawnNextLevelPortal();

	UFUNCTION(BlueprintImplementableEvent, Category = LevelBlueprint)
		void EndLevel();

	UFUNCTION(BlueprintImplementableEvent, Category = LevelBlueprint)
		void LoadInfo();
};
