#include "NotAnEngineCore.h"
#include <iostream>

using uint = unsigned int;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	NotAnEngineCore* app = new NotAnEngineCore("NotAnEngine", 1280, 720);
	app->Run();
	return 0;
}