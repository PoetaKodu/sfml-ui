#include "GameProjectPCH.hpp"

#include <SFML-UI/Game.hpp>
#include <SFML-UI/Core/MathSFMLInc.hpp>

namespace sfui
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

	
	// Time measurement:
	using namespace std::chrono;
	// Frame time must be put outside the loop.
	auto frameStart = IUpdatable::ClockType::now();

	while (this->getStatus() == Status::Running)
	{
		// Store how many seconds passed since last frame:
		double deltaTime = .0;
		// Calculate delta time and set "frameStart" to current time point.
		{
			using SecondsD = duration<double>;

			const auto now	= IUpdatable::ClockType::now();
			deltaTime		= duration_cast< SecondsD >( now - frameStart ).count();
			frameStart		= now;
		}
		

		// The event handling loop:
		sf::Event windowEvent;
		while (Window.pollEvent(windowEvent))
			this->handleEvent(windowEvent);

		// Perform logic update:
		{
			Textures.update(deltaTime, frameStart);
		}
		

		// Perform rendering:
		Window.clear(sf::Color::Black);
		{
			// TODO: draw scene here.
		}
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

} // namespace sfui
