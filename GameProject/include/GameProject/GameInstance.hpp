#pragma once

// Note:
// The only purpose of this file is to separate "Game" class definition and its only instantiation.

#include <GameProject/Game.hpp>

namespace gameproject
{
// Note: the definition of this global object is inside "Main.cpp" file.
extern Game GameInstance;
}
