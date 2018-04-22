#include "GameProjectPCH.hpp"

#include <GameProject/Game.hpp>
#include <GameProject/Core/MathSFMLInc.hpp>

namespace gameproject
{

////////////////////////////////////////////////////////////////////////////
Game::Game()
	:
	m_status{ Status::Initializing }
{
}

////////////////////////////////////////////////////////////////////////////
Game::~Game()
{
	this->cleanUp();
}

////////////////////////////////////////////////////////////////////////////
void Game::run()
{
	this->initialize();

	this->setStatus(Status::Running);

	while (this->getStatus() == Status::Running)
	{
		// The event handling loop:
		sf::Event windowEvent;
		while (Window.pollEvent(windowEvent))
			this->handleEvent(windowEvent);

		// Logic loop:
		// TODO: update logic here.

		// Display loop:
		Window.clear(sf::Color::Black);
		// TODO: draw scene here.
		Window.display();
	}
}

////////////////////////////////////////////////////////////////////////////
void Game::setStatus(Status const status_)
{
	m_status = status_;
}

////////////////////////////////////////////////////////////////////////////
void Game::cleanUp()
{
	if (Window.isOpen())
		Window.close();
}

////////////////////////////////////////////////////////////////////////////
void Game::initialize()
{
	// Consider this function as initialization process, in which when anything fails, you can throw an exception...
	// ... and handle it inside `Game::run()` method.

	Window.create(sf::VideoMode(800, 600), "GameProject App");
}

////////////////////////////////////////////////////////////////////////////
void Game::handleEvent(sf::Event const event_)
{
	if (event_.type == sf::Event::Closed)
	{
		m_status = Status::CleaningUp;
	}
}

} // namespace gameproject