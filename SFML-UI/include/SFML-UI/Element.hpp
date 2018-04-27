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
	enum class AttachPolicy
	{
		Unchecked,	// Do not check whether element can be properly added - assume it is not in this scene yet.
		Checked		// Check if element was already in this scene.
	};
	
	/// <summary>
	/// List of transform behaviour on reparenting.
	/// </summary>
	enum class AttachTransform
	{
		KeepAbsolute,	// Element does not change its world transform and is not attached to parent.
		KeepRelative,	// Element does not change its world transform but moves with parent.
		SnapToTarget	// Element transform is zeroed (relative to parent) and moves with parent.
	};

	// Aliases:

	using ElementPtrType	= std::shared_ptr< Element >;
	using ElementPoolType	= std::vector< ElementPtrType >;

	// Methods:
	
	/// <summary>
	/// Initializes a new instance of the <see cref="Element"/> class.
	/// </summary>
	Element();
		
	/// <summary>
	/// Spawns an element inside this scene.
	/// </summary>
	/// <returns>Reference to the created element.</returns>
	template <typename TElementType>		
	TElementType& spawn()
	{
		if (auto element = std::make_shared<TElementType>())
		{
			this->attach( std::move(element), AttachTransform::SnapToTarget, AttachPolicy::Unchecked );
			return *element;
		}
		else // Something inside `make_shared` failed, most probably allocation.
			throw std::runtime_error("Could not spawn element inside the scene.");
	}
		
	/// <summary>
	/// Adds the specified element to the scene.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <param name="transform_">The transform mode.</param>
	/// <param name="policy_">The attaching policy.</param>
	/// <returns>
	///   <c>true</c> if succeeded; otherwise, <c>false</c>.
	/// </returns>
	bool attach(ElementPtrType && element_, AttachTransform const transform_, AttachPolicy const policy_ = AttachPolicy::Checked);
		
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
	/// Sets the z index of the current instance.
	/// </summary>
	/// <param name="newZIndex_">New z index.</param>
	void setZIndex(std::int32_t const newZIndex_);

	/// <summary>
	/// Returns cref to element pool.
	/// </summary>
	/// <returns>const-ref to element pool.</returns>
	ElementPoolType const& getChildren() const {
		return m_children;
	}

	/// <summary>
	/// Calculates the absolute transform of specified transformable.
	/// </summary>
	/// <param name="objectWithRelativeTransform_">The object with relative transform.</param>
	/// <returns>Absolute transform.</returns>
	sf::Transform calculateAbsoluteTransform(const sf::Transformable &objectWithRelativeTransform_) const
	{
		return objectWithRelativeTransform_.getTransform() * this->getWorldTransform();
	}
	
	/// <summary>
	/// Returns parent of the current instance.
	/// </summary>
	/// <returns>Parent of the current instance.</returns>
	Element* getParent() const {
		return m_parent;
	}
	
	/// <summary>
	/// Return z index of the current instance.
	/// </summary>
	/// <returns>Z index of the current instance.</returns>
	std::int32_t getZIndex() const {
		return m_zIndex;
	}
	
	/// <summary>
	/// Returns the world transform.
	/// </summary>
	/// <returns>World transform.</returns>
	sf::Transform getWorldTransform() const {
		return m_worldTransform;
	}

	// Overriden methods from IUpdatable:
	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="deltaTime_">Time that passed since previous frame.</param>
	/// <param name="frameTime_">The frame start time.</param>
	virtual void update(double const deltaTime_, TimePoint const & frameTime_) override;


	// Memory management methods:

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

protected:
	// Methods:
	// Overriden methods from sf::Drawable:
	/// <summary>
	/// Draws the entire scene on specified target.
	/// </summary>
	/// <param name="target_">The target.</param>
	/// <param name="states_">The render states.</param>
	virtual void draw(sf::RenderTarget & target_, sf::RenderStates states_) const override;
	
	/// <summary>
	/// Sets the element's parent.
	/// </summary>
	/// <param name="parent_">The parent.</param>
	void setParent(Element* parent_, AttachTransform const transform_);

	/// <summary>
	/// Recalculates the children order.
	/// </summary>
	void recalculateChildrenOrder();

	/// <summary>
	/// Reinserts the child to match z-index order.
	/// </summary>
	void reinsertChildWithOrder(Element & element_);

	/// <summary>
	/// Finds the element inside the pool.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <returns>Iterator of the element pool, pointing to either the element or the end().</returns>
	ElementPoolType::const_iterator findChild(const Element& element_) const;

	/// <summary>
	/// Finds the element inside the pool.
	/// </summary>
	/// <param name="element_">The element.</param>
	/// <returns>Iterator of the element pool, pointing to either the element or the end().</returns>
	ElementPoolType::iterator findChild(const Element& element_);
	
	/// <summary>
	/// Finds the place in children pool for new element.
	/// </summary>
	/// <returns>Iterator in which new child should be inserted.</returns>
	ElementPoolType::const_iterator findPlaceForNewElement(const Element & element_) const;

	// Events behaviour:
	
	/// <summary>
	/// Called when direct child element changes Z index.
	/// </summary>
	/// <param name="element_">The element.</param>
	virtual void whenChildChangesZIndex(Element & element_);

	// Members:

	ElementPoolType m_children;				// Every direct child element is stored inside this container.
	Element*		m_parent;				// Element's parent in the UI tree. nullptr if this element is a root.
private:
	std::int32_t	m_zIndex;				// Index used to determine which element of the siblings (inside parent's draw and update loop) will be considered first. The lower the z-index is, the earlier element is processed.
	bool			m_relativeTransform;	// Determines whether object moves with its parent or not.
};

}