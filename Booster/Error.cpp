#include "Booster.h"

int Error(std::string error)
{
	std::cout << error << " Error code: " << ::GetLastError() << std::endl;
	return 1;
}