#include "randomization.h"

std::default_random_engine generator;

void initRandomization()
{
	generator.seed(std::chrono::system_clock::now().time_since_epoch().count());
}

unsigned naive_d6()
{
	std::uniform_int_distribution<int> distribution(1, 100);
	return distribution(generator);
}
