#pragma once

#include GAMEPROJECT_PCH

#include "MathInc.hpp"

namespace math
{

/// <summary>
/// Converts math::Vector2 to sf::Vector2.
/// </summary>
/// <param name="vector_">The custom vector.</param>
/// <returns>sf::Vector2 with value equal to passed math::Vector2 value.</returns>
template <typename TType>
inline sf::Vector2<TType> toSFMLVector(const math::Vector2<TType> &vector_)
{
	return sf::Vector2<TType>{ vector_.x, vector_.y };
}

/// <summary>
/// Converts sf:Vector2 to math::Vector2.
/// </summary>
/// <param name="vector_">The SFML vector.</param>
/// <returns>math::Vector2 with value equal to passed sf::Vector2 value.</returns>
template <typename TType>
inline math::Vector2<TType> fromSFMLVector(const sf::Vector2<TType> &vector_)
{
	return math::Vector2<TType>{ vector_.x, vector_.y };
}

/// <summary>
/// Converts math::Vector3 to sf::Vector3.
/// </summary>
/// <param name="vector_">The custom vector.</param>
/// <returns>sf::Vector3 with value equal to passed math::Vector3 value.</returns>
template <typename TType>
inline sf::Vector3<TType> toSFMLVector(const math::Vector3<TType> &vector_)
{
	return sf::Vector2<TType>{ vector_.x, vector_.y, vector_.z };
}

/// <summary>
/// Converts sf:Vector3 to math::Vector3.
/// </summary>
/// <param name="vector_">The SFML vector.</param>
/// <returns>math::Vector3 with value equal to passed sf::Vector3 value.</returns>
template <typename TType>
inline math::Vector3<TType> fromSFMLVector(const sf::Vector3<TType> &vector_)
{
	return math::Vector2<TType>{ vector_.x, vector_.y, vector_.z };
}

}