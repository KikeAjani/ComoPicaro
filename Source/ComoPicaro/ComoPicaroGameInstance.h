// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Characters/MainCharacter.h"
#include "Habilities/PowerUp.h"
#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ComoPicaroGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class COMOPICARO_API UComoPicaroGameInstance : public UGameInstance
{
	GENERATED_BODY()

		public:
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		TArray<APowerUp*> PlayerListPowerUp;


		//-----------------------------------------------
		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		 int32 ActualHealth;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			int32 Health;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			int32 SimpleAttackSpeed;



		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			int32 ExtraDamageSimpleAttack;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			int32 NumOfFireComponents;


		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			int32 LevelDificulty = 10;

		UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
			bool HasInitiallyLoaded = false;
};
