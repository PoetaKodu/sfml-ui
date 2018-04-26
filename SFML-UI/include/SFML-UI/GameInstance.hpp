#pragma once

// Note:
// The only purpose of this file is to separate "Game" class definition and its only instantiation.

#include <SFML-UI/Game.hpp>
#include <SFML-UI/Core/Pointers.hpp>

namespace sfui
{
// Note: the definition of this global object is inside "Main.cpp" file.
extern UniquePtr<Game> GameInstance;
}
