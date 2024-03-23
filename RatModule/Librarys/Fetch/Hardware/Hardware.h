#ifndef HARDWAREGETTER
#define HARDWAREGETTER
#include <Windows.h>
#include <iostream>
#include <string>
#include <comdef.h>
#include <WbemIdl.h>
#include "Xor/Xor.h"

#pragma comment(lib, "wbemuuid.lib")


class Hardware
{
public:
	//going to add more hardware info getters soon
	std::string id();

};

#endif HARDWAREGETTER