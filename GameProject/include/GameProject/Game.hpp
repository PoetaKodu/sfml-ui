#pragma once

#include GAMEPROJECT_PCH

namespace gameproject
{

/// <summary>
/// Responsible for entire gameplay.
/// </summary>
class Game
{
public:	
	// Enums:

	/// <summary>
	/// Lists every possible state of the game.
	/// </summary>
	enum class Status
	{
		Initializing,
		Running,
		CleaningUp
	};
	
	// Methods:

	/// <summary>
	/// Initializes a new instance of the <see cref="Game"/> class.
	/// </summary>
	Game();
	
	/// <summary>
	/// Finalizes an instance of the <see cref="Game"/> class.
	/// </summary>
	~Game();
	
	/// <summary>
	/// Runs the game.
	/// </summary>
	void run();
	
	/// <summary>
	/// Returns game status.
	/// </summary>
	/// <returns>Game status.</returns>
	Status getStatus() const {
		return m_status;
	}

	// Members:
	sf::RenderWindow		Window;				/// The game window.
private:
	
	// Methods:

	/// <summary>
	/// Initializes window and other settings.
	/// </summary>
	void initialize();

	/// <summary>
	/// Perform complete cleanup.
	/// </summary>
	void cleanUp();

	/// <summary>
	/// Handles specified window event.
	/// </summary>
	/// <param name="event_">The event.</param>
	void handleEvent(sf::Event const event_);

	// Members:

	Status					m_status;			/// The game status.
};

}
