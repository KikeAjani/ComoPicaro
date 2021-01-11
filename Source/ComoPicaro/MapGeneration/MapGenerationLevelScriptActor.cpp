// Fill out your copyright notice in the Description page of Project Settings.
#include "MapGenerationLevelScriptActor.h"
#include "Engine/Classes/Kismet/GameplayStatics.h"

void AMapGenerationLevelScriptActor::BeginPlay()
{
	Super::BeginPlay();
	LoadInfo();
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

			int32 randomRotation = FMath::RandRange(0, 3);
			randomRotation *= 90;
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
	int32 levelDificulty = static_cast<UComoPicaroGameInstance*>(UGameplayStatics::GetGameInstance(this))->LevelDificulty;
	while (totalDificultyAdded < levelDificulty) {
		int32 randomNum = FMath::RandRange(0, EnemyTypes.Num() - 1);
		TSubclassOf<AEnemy> enemyClass = EnemyTypes[randomNum];
		int32 enemyDificulty = enemyClass.GetDefaultObject()->Dificulty;
		while (enemyDificulty + totalDificultyAdded > levelDificulty) {
			randomNum--;
			if (randomNum < 0) {
				break;
			}
			randomNum = FMath::RandRange(0, randomNum);
			enemyClass = EnemyTypes[randomNum];
			enemyDificulty = enemyClass.GetDefaultObject()->Dificulty;
		}
		if (randomNum < 0) {
			break;
		}
		ATileLevelScriptActor* tile;
		do {
			tile = GetRandomTileScriptActor();
		} while (tile->HasEnemySpawned);
		AEnemy* enemy = tile->SpawnEnemy(enemyClass);
		enemy->DyingEnemyDelegate.AddDynamic(this, &AMapGenerationLevelScriptActor::EnemyDeath);
		EnemyNum++;
		totalDificultyAdded += enemyDificulty;
	}
}

void AMapGenerationLevelScriptActor::EnemyDeath()
{
	EnemyNum--;
	if (EnemyNum <= 0) {
		SpawnRandomPowerUp();
	}
}

void AMapGenerationLevelScriptActor::SpawnRandomPowerUp()
{
	int32 randomNum = FMath::RandRange(0, PowerUpTypes.Num() - 1);
	TSubclassOf<APowerUp> powerUpClass = PowerUpTypes[randomNum];

	FTransform spawnTransform;
	spawnTransform.SetLocation(FVector(0, 0, 100));

	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	AActor* powerUpActor = GetWorld()->SpawnActorAbsolute(powerUpClass, spawnTransform, spawnParams);

	powerUpActor->SetActorScale3D(FVector(2, 2, 2));

	EndLevel();
}
