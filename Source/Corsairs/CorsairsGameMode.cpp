// Copyright Epic Games, Inc. All Rights Reserved.

#include "CorsairsGameMode.h"
#include "CorsairsCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Twinblast.h"

ACorsairsGameMode::ACorsairsGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}

	DefaultPawnClass = ATwinblast::StaticClass();
}
