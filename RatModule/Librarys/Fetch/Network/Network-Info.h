#ifndef NETWORKSTUFF
#define NETWORKSTUFF
#include <Windows.h>
#include <iostream>
#include <WinINet.h>

#include <iomanip>
#include <iphlpapi.h>
#include <sstream>
#include <vector>
#include <string>
#include "Xor/Xor.h"

#pragma comment(lib, "IPHLPAPI.lib")
#pragma comment(lib, "wininet.lib")

class Network
{
public:

	std::string ip();
	std::string mac_address();
	

private:
	std::string get_public_ip();
	std::string get_mac_address();

	

};

#endif


