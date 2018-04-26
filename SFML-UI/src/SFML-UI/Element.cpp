#include "GameProjectPCH.hpp"

#include <SFML-UI/Element.hpp>

namespace sfui
{

//////////////////////////////////////////////////////////////////////////////
bool Element::add(const ElementPtrType & element_, const AddPolicy policy_)
{
	if (element_)
	{
		if (policy_ == AddPolicy::Unchecked || !this->contains(*element_) )
		{
			m_children.push_back(element_);
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
bool Element::remove(const Element & element_)
{
	const auto it = this->findChild(element_);
	if (it != m_children.end())
	{
		m_children.erase(it);
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
bool Element::contains(const Element & element_) const
{
	return (this->findChild(element_) != m_children.end());
}

//////////////////////////////////////////////////////////////////////////////
void Element::update(const double deltaTime_, const IUpdatable::TimePoint & frameTime_)
{
	for (const auto & actor : m_children)
		actor->update(deltaTime_, frameTime_);
}

//////////////////////////////////////////////////////////////////////////////
void Element::draw(sf::RenderTarget & target_, sf::RenderStates states_) const
{
	for (const auto & actor : m_children)
		actor->draw(target_, states_);
}

//////////////////////////////////////////////////////////////////////////////
Element::ElementPoolType::const_iterator Element::findChild(const Element & element_) const
{
	return std::find_if(
			m_children.begin(),
			m_children.end(),
			// This lambda function must tell whether the element is equal to what we are looking for.
			[&element_](const ElementPtrType & element_)
			{
				// Check if "element_" points to the actor.
				return element_.get() == &element_;
			}
		);
}

}