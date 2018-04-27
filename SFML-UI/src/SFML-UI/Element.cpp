#include "SFMLUIPCH.hpp"

#include <SFML-UI/Element.hpp>
#include <SFML-UI/Core/Transform.hpp>

namespace sfui
{

//////////////////////////////////////////////////////////////////////////////
Element::Element()
	:
	m_parent{ nullptr },
	m_zIndex{ 0 },
	m_relativeTransform{ true }
{
}

//////////////////////////////////////////////////////////////////////////////
bool Element::attach(ElementPtrType && element_, AttachTransform const transform_, AttachPolicy const policy_)
{
	if (element_)
	{
		if (policy_ == AttachPolicy::Unchecked || !this->contains(*element_) )
		{
			auto const whereToInsert = this->findPlaceForNewElement(*element_);
			element_->setParent(this, transform_);
			m_children.emplace(whereToInsert, std::forward<ElementPtrType>(element_) );
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
bool Element::remove(Element const & element_)
{
	auto const it = this->findChild(element_);
	if (it != m_children.end())
	{
		m_children.erase(it);
		return true;
	}
	return false;
}

//////////////////////////////////////////////////////////////////////////////
bool Element::contains(Element const & element_) const
{
	return (this->findChild(element_) != m_children.end());
}

//////////////////////////////////////////////////////////////////////////////
void Element::setZIndex(std::int32_t const newZIndex_)
{
	m_zIndex = newZIndex_;
	if(m_parent)
		m_parent->whenChildChangesZIndex(*this);
}

//////////////////////////////////////////////////////////////////////////////
void Element::setTransform(sf::Transform const & newTransform_)
{
	namespace algo = transform_algorithm;

	this->setPosition(algo::extractPosition(newTransform_));
	this->setRotation(algo::extractRotation(newTransform_));
	this->setScale(algo::extractScale(newTransform_));
}

//////////////////////////////////////////////////////////////////////////////
sf::Transform Element::getWorldTransform() const
{
	if (m_parent && m_relativeTransform)
		return m_parent->mapToWorldTransform(this->getTransform());
	else
		return this->getTransform();
}

//////////////////////////////////////////////////////////////////////////////
void Element::update(double const deltaTime_, const TimePoint & frameTime_)
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
void Element::setParent(Element * parent_, AttachTransform const transform_)
{
	switch (transform_)
	{
	case AttachTransform::KeepAbsolute:
	{
		auto const worldTransform = this->getWorldTransform();
		this->setTransform(worldTransform);

		m_relativeTransform = false;
		break;
	}
	case AttachTransform::KeepRelative:
	{
		m_relativeTransform = true;
		// TODO: implement this.	
		break;
	}
	case AttachTransform::SnapToTarget:
	{
		m_relativeTransform = true;
		this->setTransform(sf::Transform::Identity);
		break;
	}
	default: ;
	}
	m_parent = parent_;
}

//////////////////////////////////////////////////////////////////////////////
Element::ElementPoolType::const_iterator Element::findChild(Element const & element_) const
{
	return std::find_if(
			m_children.cbegin(),
			m_children.cend(),
			// This lambda function must tell whether the element is equal to what we are looking for.
			[&element_](const ElementPtrType & vecElement_)
			{
				// Check if "element_" points to the actor.
				return vecElement_.get() == &element_;
			}
		);
}

//////////////////////////////////////////////////////////////////////////////
Element::ElementPoolType::iterator Element::findChild(Element const & element_)
{
	return std::find_if(
		m_children.begin(),
		m_children.end(),
		// This lambda function must tell whether the element is equal to what we are looking for.
		[&element_](const ElementPtrType & vecElement_)
	{
		// Check if "element_" points to the actor.
		return vecElement_.get() == &element_;
	}
	);
}

//////////////////////////////////////////////////////////////////////////////
Element::ElementPoolType::const_iterator Element::findPlaceForNewElement(const Element & element_) const
{
	return std::upper_bound(m_children.begin(), m_children.end(), element_.getZIndex(),
		[](std::int32_t const lhs_, ElementPtrType const & rhs_)
		{
			return lhs_ < rhs_->getZIndex();
		});
}

//////////////////////////////////////////////////////////////////////////////
void Element::whenChildChangesZIndex(Element & element_)
{
	// element_ stays unused
	this->reinsertChildWithOrder(element_);
}

//////////////////////////////////////////////////////////////////////////////
void Element::recalculateChildrenOrder()
{
	std::sort(m_children.begin(), m_children.end(),
		[](ElementPtrType const &lhs_, ElementPtrType const & rhs_)
		{
			return lhs_->getZIndex() < rhs_->getZIndex();
		});
}

//////////////////////////////////////////////////////////////////////////////
void Element::reinsertChildWithOrder(Element & element_)
{
	auto const it = this->findChild(element_);

	if (it == m_children.end())
		throw std::invalid_argument("Given element is not a child of this element.");

	// Store rvalue reference to found element before iterators will be invalidated.
	ElementPtrType&& rRef = std::move(*it);

	// Erase empty child:
	m_children.erase(it);

	// Find the place where it should be reinserted:
	auto const whereToInsert = this->findPlaceForNewElement(*rRef);

	// Insert it:
	m_children.emplace( whereToInsert, std::forward<ElementPtrType>(rRef) );

	// rRef is invalid here. 
}

}