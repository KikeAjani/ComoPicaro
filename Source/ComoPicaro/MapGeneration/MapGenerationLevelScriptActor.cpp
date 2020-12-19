// Fill out your copyright notice in the Description page of Project Settings.

#include "Engine/Classes/Kismet/GameplayStatics.h"
#include "MapGenerationLevelScriptActor.h"

void AMapGenerationLevelScriptActor::GenerateRoom()
{
	float gridCenter = (TileSize * (GridSize - 1)) / 2;
	for (int32 i = 0; i < GridSize; i++)
	{
		for (int32 j = 0; j < GridSize; j++)
		{
			//Get random tile as streaming level
			int32 randomInt = FMath::RandRange(1, NumOfTilesCreated);
			FString tileString("Tile");
			tileString.AppendInt(randomInt);
			FName tileName(tileString);
			ULevelStreaming* randomLevel = UGameplayStatics::GetStreamingLevel(this, tileName);
			ensure(randomLevel);

			//Create level instance with name "ixj"
			FString levelInstanceName = FString::FromInt(i);
			levelInstanceName.Append("x");
			levelInstanceName.AppendInt(j);
			randomLevel = randomLevel->CreateInstance(levelInstanceName);

			//Set transform of level (grid location and random rotation*90)
			FTransform tileTransform;

			float tileX = (i * TileSize) - gridCenter;
			float tileY = (j * TileSize) - gridCenter;
			FVector tileLocation(tileX, tileY, 0);
			tileTransform.SetLocation(tileLocation);

			int32 randomRotation = FMath::RandRange(0, 359);
			FRotator tileRotation(0, randomRotation, 0);
			tileTransform.SetRotation(tileRotation.Quaternion());

			randomLevel->LevelTransform = tileTransform;

			//Set loaded and visible
			randomLevel->SetShouldBeLoaded(true);
			randomLevel->SetShouldBeVisible(true);
		}
	}
}
