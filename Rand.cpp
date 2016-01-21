#include <cstdlib>
#include "Headers\Rand.h"

// Returns an integer value between min and max inclusive
int getRand(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Returns a random boolean value
bool getBool() {
	switch (rand() % 2) {
	case 0:
		return true;
		break;
	case 1:
		return false;
		break;
	default:
		// Someone broke the universe again...
		return true;
		break;
	};
}

// Returns either +1 or -1
int getPlMn() {
	return getBool() ? 1 : -1;
}