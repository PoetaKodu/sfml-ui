#include "GameProjectPCH.hpp"

#include <GameProject/Scene.hpp>

namespace gameproject
{

//////////////////////////////////////////////////////////////////////////////
bool Scene::add(const ActorPtrType & actor_, const AddPolicy policy_)
{
	if (actor_)
	{
		if (policy_ == AddPolicy::Unchecked || ! this->contains(*actor_) )
		{
			m_actors.push_back(actor_);
		}
	}
}

//////////////////////////////////////////////////////////////////////////////
bool Scene::remove(const IActor & actor_)
{
	auto it = this->findActor(actor_);
	if (it != m_actors.end())
	{
		m_actors.erase(it);
	}
}

//////////////////////////////////////////////////////////////////////////////
bool Scene::contains(const IActor & actor_) const
{
	return (this->findActor(actor_) != m_actors.end());
}

//////////////////////////////////////////////////////////////////////////////
void Scene::update(double deltaTime_, const IUpdatable::TimePoint & frameTime_)
{
	for (const auto & actor : m_actors)
		actor->update(deltaTime_, frameTime_);
}

//////////////////////////////////////////////////////////////////////////////
void Scene::draw(sf::RenderTarget & target_, sf::RenderStates states_) const
{
	for (const auto & actor : m_actors)
		actor->draw(target_, states_); // TODO: implement draw.
}

//////////////////////////////////////////////////////////////////////////////
Scene::ActorPoolType::const_iterator Scene::findActor(const IActor & actor_) const
{
	return std::find_if(
			m_actors.begin(),
			m_actors.end(),
			// This lambda function must tell whether the element is equal to what we are looking for.
			[&actor_](const ActorPtrType & element_)
			{
				// Check if "element_" points to the actor.
				return element_.get() == &actor_;
			}
		);
}

}