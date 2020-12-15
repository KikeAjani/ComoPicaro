// Copyright Epic Games, Inc. All Rights Reserved.

#include "ComoPicaroGameMode.h"
#include "ComoPicaroPawn.h"

AComoPicaroGameMode::AComoPicaroGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = AComoPicaroPawn::StaticClass();
}

