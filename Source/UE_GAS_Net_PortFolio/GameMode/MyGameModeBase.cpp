#include "GameMode/MyGameModeBase.h"
#include "PlayerState/MyPlayerState.h"
#include "Controller/MyPlayerController.h"
#include "Character/MyPlayer.h"

AMyGameModeBase::AMyGameModeBase()
{
	static ConstructorHelpers::FClassFinder<AMyPlayer> PlayerClass(TEXT("/Game/Character/Player/BP_Player"));
	if (PlayerClass.Succeeded())
		DefaultPawnClass = PlayerClass.Class;

	static ConstructorHelpers::FClassFinder<AMyPlayerState> StateClass(TEXT("/Game/PlayerState/BP_PlayerState"));
	if (StateClass.Succeeded())
		PlayerStateClass = StateClass.Class;

	static ConstructorHelpers::FClassFinder<AMyPlayerController> ControllerClass(TEXT("/Game/Controller/BP_PlayerController"));
	if (ControllerClass.Succeeded())
		PlayerControllerClass = ControllerClass.Class;
}
