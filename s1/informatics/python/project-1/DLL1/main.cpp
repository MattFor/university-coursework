//
// Created by MattFor on 23/04/2025.
//

#include <thread>
#include <iostream>

#include "SOUNDLIB.hpp"

int main()
{
	std::cout << "Playing 440 Hz tone for 1 second...\n";
	playTone(440.0f, 1000);

	std::this_thread::sleep_for(std::chrono::milliseconds(1100));
}
