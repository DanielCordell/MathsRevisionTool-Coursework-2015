#ifndef PAUSEABLECLOCK_HPP
#define PAUSEABLECLOCK_HPP

#include <SFML/System.hpp>

namespace sf {
	class PauseableClock {
		sf::Clock internalClock;
		bool paused;
		static bool universalpause;
		sf::Time pcTime;

	public:

		// Think must be run for the instanced Pauseableclock to support
		// Universal Pause. If not run, will work/pause normally but Universal Pausing
		// will not be supported.
		void think();

		void pause();
		void start();
		const sf::Time getElapsedTime();
		sf::Time restart(const bool pause = false);

		static void universalPause();
		static void universalStart();

		PauseableClock();
	};
}
#endif