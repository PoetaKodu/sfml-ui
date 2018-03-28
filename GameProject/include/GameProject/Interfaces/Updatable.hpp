#pragma once

namespace gameproject
{	
	/// <summary>
	/// Basic interface for everything that should be update every frame.
	/// </summary>
	struct IUpdatable {
		using TimePoint = std::chrono::high_resolution_clock::time_point;

		/// <summary>
		/// Updates this instance.
		/// </summary>
		/// <param name="deltaTime_">Time that passed since previous frame.</param>
		/// <param name="frameTime_">The frame start time.</param>
		virtual void update(double deltaTime_, const IUpdatable::TimePoint & frameTime_) = 0;
	};
}
