#pragma once

#include GAMEPROJECT_PCH

#include <GameProject/Interfaces/Updatable.hpp>
#include <GameProject/Core/Memory.hpp>

namespace gameproject
{
	
/// <summary>
/// A base class for every object that can exist on scene.
/// </summary>
/// <seealso cref="IUpdatable" />
/// <seealso cref="std::enable_shared_from_this{IActor}" />
/// <seealso cref="sf::Drawable" />
class IActor
	:
	public IUpdatable,
	public sf::Drawable,
	private std::enable_shared_from_this<IActor>
{
public:
	// Methods:

	/// <summary>
	/// Gets the weak pointer to self (const).
	/// </summary>
	/// <returns>Weak pointer to self (const).</returns>
	WeakPtr<const IActor> getWeakPtr() const {
		return this->weak_from_this();
	}
	
	/// <summary>
	/// Gets the weak pointer to self.
	/// </summary>
	/// <returns>Weak pointer to self.</returns>
	WeakPtr<IActor> getWeakPtr() {
		return this->weak_from_this();
	}
	
	/// <summary>
	/// Gets shared pointer to self (const). Uses dynamic cast when specified type other than IActor.
	/// </summary>
	/// <returns>Gets shared pointer to self (const).</returns>
	template <typename TActorType = IActor>	
	SharedPtr<const TActorType> getSharedPtr() const {
		return std::dynamic_pointer_cast<const TActorType>( this->shared_from_this() );
	}

	/// <summary>
	/// Gets shared pointer to self. Uses dynamic cast when specified type other than IActor.
	/// </summary>
	/// <returns>Gets shared pointer to self.</returns>
	template <typename TActorType = IActor>
	SharedPtr<TActorType> getSharedPtr() {
		return std::dynamic_pointer_cast<TActorType>( this->shared_from_this() );
	}

protected:
	// Methods:
	// Overriden from sf::Drawable:
	/// <summary>
	/// Draws the specified target.
	/// </summary>
	/// <param name="target_">The target.</param>
	/// <param name="states_">The states.</param>
	virtual void draw(sf::RenderTarget & target_, sf::RenderStates states_) const override {
		// Nothing by default.
	}
};

}
