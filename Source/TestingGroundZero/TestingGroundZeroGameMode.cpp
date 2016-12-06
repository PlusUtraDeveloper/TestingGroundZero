// Copyright 1998-2016 Epic Games, Inc. All Rights Reserved.

#include "TestingGroundZero.h"
#include "TestingGroundZeroGameMode.h"
#include "TestingGroundZeroHUD.h"
#include "Player/FirstPersonPlayer.h"

ATestingGroundZeroGameMode::ATestingGroundZeroGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/Player/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ATestingGroundZeroHUD::StaticClass();
}
