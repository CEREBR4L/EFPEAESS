// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "EFPEAESS.h"
#include "EFPEAESSGameMode.h"
#include "EFPEAESSHUD.h"
#include "Player/FirstPersonCharacter.h"

AEFPEAESSGameMode::AEFPEAESSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Behaviour/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AEFPEAESSHUD::StaticClass();
}
