#pragma once

#include SFMLUI_PCH

namespace sfui
{
	
namespace transform_algorithm
{

/// <summary>
/// Extracts position from specified transform.
/// </summary>
/// <param name="transform_"></param>
/// <returns>Extracted position.</returns>
sf::Vector2f extractPosition(sf::Transform const & transform_);

/// <summary>
/// Extracts scale from specified transform.
/// </summary>
/// <param name="transform_"></param>
/// <param name="xyz_"></param>
/// <returns>Extracted scale.</returns>
sf::Vector2f extractScale(sf::Transform const & transform_);


/// <summary>
/// Extracts rotation from specified transform.
/// </summary>
/// <param name="transform_"></param>
/// <returns>Extracted rotation.</returns>
float extractRotation(sf::Transform const & transform_);

}

}
