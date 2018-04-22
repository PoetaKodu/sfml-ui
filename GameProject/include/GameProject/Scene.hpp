#pragma once

#include GAMEPROJECT_PCH

#include <GameProject/Interfaces/Updatable.hpp>
#include <GameProject/Actors/Actor.hpp>

namespace gameproject
{

/// <summary>
/// Contains and manages every actor inside.
/// </summary>
class Scene
	:
	public sf::Drawable,
	public IUpdatable
{
public:
	// Enums:
		
	/// <summary>
	/// Lists the behaviour of "Scene::add" function.
	/// </summary>
	enum class AddPolicy
	{
		Unchecked,	// Do not check whether actor can be properly added - assume it is not in this scene yet.
		Checked		// Check if actor was already in this scene.
	};

	// Aliases:

	using ActorPtrType		= std::shared_ptr< IActor >;
	using ActorPoolType		= std::vector< ActorPtrType >;

	// Methods:
		
	/// <summary>
	/// Spawns an actor inside this scene.
	/// </summary>
	/// <returns>Reference to the created actor.</returns>
	template <typename TActorType>		
	TActorType& spawn()
	{
		if (auto actor = std::make_shared<TActorType>())
		{
			this->add(actor, AddPolicy::Unchecked);
			return *actor;
		}
		else // Something inside `make_shared` failed, most probably allocation.
			throw std::runtime_error("Could not spawn actor inside the scene.");
	}
		
	/// <summary>
	/// Adds the specified actor to the scene.
	/// </summary>
	/// <param name="actor_">The actor.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool add(const ActorPtrType & actor_, const AddPolicy policy_ = AddPolicy::Checked);
		
	/// <summary>
	/// Removes the specified actor from the scene.
	/// </summary>
	/// <param name="actor_">The actor.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool remove(const IActor& actor_);
		
	/// <summary>
	/// Determines whether scene contains the specified actor.
	/// </summary>
	/// <param name="actor_">The actor.</param>
	/// <returns>
	///		<c>true</c> if contains; otherwise, <c>false</c>.
	/// </returns>
	bool contains(const IActor& actor_) const;

	/// <summary>
	/// Returns cref to actor pool.
	/// </summary>
	/// <returns>const-ref to actor pool.</returns>
	const ActorPoolType& getActors() const {
		return m_actors;
	}

	// Overriden methods from IUpdatable:
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="deltaTime_">Time that passed since previous frame.</param>
	/// <param name="frameTime_">The frame start time.</param>
	virtual void update(const double deltaTime_, const IUpdatable::TimePoint & frameTime_) override;

protected:
	// Methods:
	// Overriden methods from sf::Drawable:
	/// <summary>
	/// Draws the entire scene on specified target.
	/// </summary>
	/// <param name="target_">The target.</param>
	/// <param name="states_">The render states.</param>
	virtual void draw(sf::RenderTarget & target_, sf::RenderStates states_) const override;
	
private:
	// Methods:

	/// <summary>
	/// Finds the actor inside the pool.
	/// </summary>
	/// <param name="actor_">The actor.</param>
	/// <returns>Iterator of the actor pool, pointing to either the actor or the end().</returns>
	ActorPoolType::const_iterator findActor(const IActor& actor_) const;

	// Members:

	ActorPoolType m_actors;		/// Every actor is stored inside this container.
};

}