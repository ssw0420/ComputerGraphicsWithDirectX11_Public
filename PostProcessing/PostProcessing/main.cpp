#include <iostream>
#include <memory>
#include <windows.h>

#include "DemoApp.h"

using namespace std;

int main()
{
	ssw::DemoApp demoApp;

	if (!demoApp.Initialize())
	{
		cout << "Demo Application Initialization FAILED" << endl;
		return -1;
	}

	return demoApp.Run();
}