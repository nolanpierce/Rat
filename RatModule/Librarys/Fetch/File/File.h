#ifndef FILESTUFF
#define FILESTUFF
#include <Windows.h>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <vector>
#include <string>
#include "Xor/Xor.h"

class File
{
public:
	File(const std::string& fname) : file_name(fname) {}

	std::string path();
	std::string name();
	std::vector<uint8_t> image();

private:
	std::vector<std::string> all_paths();

	std::string file_path{};
	std::string file_name{};
};

#endif // !FILESTUFF



