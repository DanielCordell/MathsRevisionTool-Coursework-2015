#include <cstdlib>
#include "Headers\Rand.h"
#include <iostream>

// Returns an integer value between min and max inclusive
int getRand(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Returns a random boolean value
bool getBool() {
	return rand() % 2
}

// Returns either +1 or -1
int getPlMn() {
	return getBool() ? 1 : -1;
}
