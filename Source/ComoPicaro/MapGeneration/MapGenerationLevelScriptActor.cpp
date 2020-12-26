// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "MapGenerationLevelScriptActor.h"

void AMapGenerationLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();

	GenerateRoom();
}

void AMapGenerationLevelScriptActor::GenerateRoom()
{
	GridCenter = (TileSize * (GridSize - 1)) / 2;
	for (int32 i = 0; i < GridSize; i++)
	{
		TileGrid.Insert(FTileArray(), i);
		for (int32 j = 0; j < GridSize; j++)
		{
			//Get random tile as streaming level
			int32 randomInt = FMath::RandRange(1, NumOfTileTypes);
			FString tileString("Tile");
			tileString.AppendInt(randomInt);
			FName tileName(tileString);
			ULevelStreaming* randomTileLevel = UGameplayStatics::GetStreamingLevel(this, tileName);
			ensure(randomTileLevel != nullptr);

			//Create level instance with name "ixj"
			FString levelInstanceName = FString::FromInt(i);
			levelInstanceName.Append("x");
			levelInstanceName.AppendInt(j);
			randomTileLevel = randomTileLevel->CreateInstance(levelInstanceName);

			//Set transform of level (grid location and random rotation*90)
			FTransform tileTransform;

			float tileX = (i * TileSize) - GridCenter;
			float tileY = (j * TileSize) - GridCenter;
			FVector tileLocation(tileX, tileY, 0);
			tileTransform.SetLocation(tileLocation);

			int32 randomRotation = FMath::RandRange(0, 359);
			FRotator tileRotation(0, randomRotation, 0);
			tileTransform.SetRotation(tileRotation.Quaternion());

			randomTileLevel->LevelTransform = tileTransform;

			//Set loaded and visible
			randomTileLevel->SetShouldBeLoaded(true);
			randomTileLevel->SetShouldBeVisible(true);

			//Set OnTileLoaded Dynamic multicast delegate
			randomTileLevel->OnLevelLoaded.AddDynamic(this, &AMapGenerationLevelScriptActor::OnTileLoaded);
			TileGrid[i].Insert(randomTileLevel, j);
		}
	}
}

ATileLevelScriptActor* AMapGenerationLevelScriptActor::GetRandomTileScriptActor()
{
	int32 randomColumn = FMath::RandRange(0, GridSize - 1);
	int32 randomRow = FMath::RandRange(0, GridSize - 1);
	return static_cast<ATileLevelScriptActor*>(TileGrid[randomColumn][randomRow]->GetLevelScriptActor());
}

void AMapGenerationLevelScriptActor::OnTileLoaded()
{
	TilesLoaded++;
	if (TilesLoaded == GridSize * GridSize) {
		OnAllTilesLoaded();
	}
}

void AMapGenerationLevelScriptActor::OnAllTilesLoaded()
{
	SpawnEnemies();
}

void AMapGenerationLevelScriptActor::SpawnEnemies()
{
	int32 totalDificultyAdded = 0;
	while (totalDificultyAdded < Dificulty) {
		int32 randomNum = FMath::RandRange(0, EnemyTypes.Num() - 1);
		TSubclassOf<AEnemy> enemyClass = EnemyTypes[randomNum];
		int32 enemyDificulty = enemyClass.GetDefaultObject()->Dificulty;
		while (enemyDificulty + totalDificultyAdded > Dificulty) {
			randomNum--;
			if (randomNum < 0) {
				break;
			}
			enemyClass = EnemyTypes[randomNum];
			enemyDificulty = enemyClass.GetDefaultObject()->Dificulty;
		}
		if (randomNum < 0) {
			break;
		}
		GetRandomTileScriptActor()->SpawnEnemy(enemyClass);
		totalDificultyAdded += enemyDificulty;
	}
}
