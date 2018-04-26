#pragma once

#include SFMLUI_PCH

#include <SFML-UI/Interfaces/Updatable.hpp>
#include <SFML-UI/Core/Pointers.hpp>

namespace sfui
{

/// <summary>
/// Contains and manages every element inside.
/// </summary>
class Element
	:
	private std::enable_shared_from_this<Element>,
	public IUpdatable,
	public sf::Drawable,
	public sf::Transformable
{
public:
	// Enums:
		
	/// <summary>
	/// Lists the behaviour of "Element::add" function.
	/// </summary>
	enum class AddPolicy
	{
		Unchecked,	// Do not check whether element can be properly added - assume it is not in this scene yet.
		Checked		// Check if element was already in this scene.
	};

	// Aliases:

	using ElementPtrType	= std::shared_ptr< Element >;
	using ElementPoolType	= std::vector< ElementPtrType >;

	// Methods:
		
	/// <summary>
	/// Spawns an element inside this scene.
	/// </summary>
	/// <returns>Reference to the created element.</returns>
	template <typename TElementType>		
	TElementType& spawn()
	{
		if (auto element = std::make_shared<TElementType>())
		{
			this->add(element, AddPolicy::Unchecked);
			return *element;
		}
		else // Something inside `make_shared` failed, most probably allocation.
			throw std::runtime_error("Could not spawn element inside the scene.");
	}
		
	/// <summary>
	/// Adds the specified element to the scene.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool add(ElementPtrType const & element_, AddPolicy const policy_ = AddPolicy::Checked);
		
	/// <summary>
	/// Removes the specified element from the scene.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <returns>
	///		<c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool remove(Element const& element_);
		
	/// <summary>
	/// Determines whether scene contains the specified element.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <returns>
	///		<c>true</c> if contains; otherwise, <c>false</c>.
	/// </returns>
	bool contains(Element const& element_) const;

	/// <summary>
	/// Returns cref to element pool.
	/// </summary>
	/// <returns>const-ref to element pool.</returns>
	ElementPoolType const& getChildren() const {
		return m_children;
	}

	// Overriden methods from IUpdatable:
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="deltaTime_">Time that passed since previous frame.</param>
	/// <param name="frameTime_">The frame start time.</param>
	virtual void update(double const deltaTime_, TimePoint const & frameTime_) override;

	// Methods:

	/// <summary>
	/// Gets the weak pointer to self (const).
	/// </summary>
	/// <returns>Weak pointer to self (const).</returns>
	WeakPtr<const Element> getWeakPtr() const {
		return this->weak_from_this();
	}

	/// <summary>
	/// Gets the weak pointer to self.
	/// </summary>
	/// <returns>Weak pointer to self.</returns>
	WeakPtr<Element> getWeakPtr() {
		return this->weak_from_this();
	}

	/// <summary>
	/// Gets shared pointer to self (const). Uses dynamic cast when specified type other than Element.
	/// </summary>
	/// <returns>Gets shared pointer to self (const).</returns>
	template <typename TElementType = Element>
	SharedPtr<const TElementType> getSharedPtr() const {
		return std::dynamic_pointer_cast<const TElementType>(this->shared_from_this());
	}

	/// <summary>
	/// Gets shared pointer to self. Uses dynamic cast when specified type other than Element.
	/// </summary>
	/// <returns>Gets shared pointer to self.</returns>
	template <typename TElementType = Element>
	SharedPtr<TElementType> getSharedPtr() {
		return std::dynamic_pointer_cast<TElementType>(this->shared_from_this());
	}

	/// <summary>
	/// Calculates the absolute transform of specified transformable.
	/// </summary>
	/// <param name="objectWithRelativeTransform_">The object with relative transform.</param>
	/// <returns>Absolute transform.</returns>
	sf::Transform calculateAbsoluteTransform(const sf::Transformable &objectWithRelativeTransform_) const
	{
		return objectWithRelativeTransform_.getTransform() * this->getTransform();
	}

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
	/// Finds the element inside the pool.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <returns>Iterator of the element pool, pointing to either the element or the end().</returns>
	ElementPoolType::const_iterator findChild(const Element& element_) const;

	// Members:

	ElementPoolType m_children;		/// Every child element is stored inside this container.
};

}