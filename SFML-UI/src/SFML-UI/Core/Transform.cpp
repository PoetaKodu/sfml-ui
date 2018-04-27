#include "SFMLUIPCH.hpp"

#include <SFML-UI/Core/Transform.hpp>
#include <SFML-UI/Core/MathInc.hpp>

namespace sfui
{

namespace transform_algorithm
{

///////////////////////////////////////////////////////////////////////////
sf::Vector2f extractPosition(sf::Transform const & transform_)
{
	auto const matrix = transform_.getMatrix();
	return sf::Vector2f{ matrix[12], matrix[13] };
}

///////////////////////////////////////////////////////////////////////////
sf::Vector2f extractScale(sf::Transform const & transform_)
{
	auto const matrix = transform_.getMatrix();

	float const lenXVec = std::sqrt(matrix[0] * matrix[0] + matrix[4] * matrix[4]);
	float const lenYVec = std::sqrt(matrix[1] * matrix[1] + matrix[5] * matrix[5]);

	return sf::Vector2f{
			matrix[0] >= 0 ? lenXVec : -lenXVec,
			matrix[5] >= 0 ? lenYVec : -lenYVec
		};
}

///////////////////////////////////////////////////////////////////////////
float extractRotation(sf::Transform const & transform_)
{
	auto const matrix = transform_.getMatrix();

	return math::convertToDegrees( std::atan2(matrix[1], matrix[5]) );
}

}

}

