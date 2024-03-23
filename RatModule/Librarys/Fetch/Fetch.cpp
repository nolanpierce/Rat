#include "Fetch.h"

File Fetch::file(std::string file_name)
{
	File _file(file_name);

	return _file;
}

Network Fetch::network()
{
	return Network();
}

Hardware Fetch::hardware()
{
	return Hardware();
}

User Fetch::user()
{
	return User();
}
