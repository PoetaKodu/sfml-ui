#pragma once

namespace sfui
{	

/// <summary>
/// Basic interface for everything that should be update every frame.
/// </summary>
struct IUpdatable
{
	// Aliases:

	using ClockType = std::chrono::high_resolution_clock;
	using TimePoint = ClockType::time_point;

	// Methods:

	virtual ~IUpdatable() = default;

	/// <summary>
	/// Updates this instance.
	/// </summary>
	/// <param name="deltaTime_">Time that passed since previous frame.</param>
	/// <param name="frameTime_">The frame start time.</param>
	virtual void update(const double deltaTime_, const IUpdatable::TimePoint & frameTime_) = 0;
};

}
