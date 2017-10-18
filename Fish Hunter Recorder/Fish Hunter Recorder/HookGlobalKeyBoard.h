#pragma once
#include <iostream>
#include <windows.h>

#include "CaptureChrome.h"
#include "FeatureObserved.h"

using namespace std;

class HookGlobalKeyBoard
{
public:
	HookGlobalKeyBoard();
	~HookGlobalKeyBoard();


	static int Width;
	static int Height;
	static CaptureChrome chrome;
	static FeatureObserved featureOP;
private:

	static LRESULT CALLBACK GlobalEvent(int, WPARAM, LPARAM);
	static HHOOK hook;
};

