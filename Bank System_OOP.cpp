#include <iostream>
#include "clsLoginScreen.h"
using namespace std;

int main()
{

	while (true)
	{
		if (!clsLoginScreen::_ShowLoginScreen())
			break;

	}

	return 0;
}
