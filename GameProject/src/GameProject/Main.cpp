#include "GameProjectPCH.hpp"

#include <GameProject/Game.hpp>

using namespace gameproject;

// Note:
// This is definition of a `GameInstance` declared inside "GameProject/GameInstance.hpp"
Game GameInstance;

int main()
{
	GameInstance.run();
}

