#include "Network-Info.h"

std::string Network::ip()
{
    return this->get_public_ip();
}

std::string Network::mac_address()
{
    return this->get_mac_address();
}

std::string Network::get_public_ip()
{
    HINTERNET h_internet = InternetOpenA(
        "YourIpIsMine",
        INTERNET_OPEN_TYPE_DIRECT,
        nullptr,
        nullptr,
        NULL
    );

    if (h_internet) {
        HINTERNET h_connect = InternetOpenUrlA(
            h_internet,
            "http://ifconfig.co/ip",
            nullptr,
            0,
            INTERNET_FLAG_RELOAD,
            0
        );
        if (h_connect) {

            char buffer[1024];
            DWORD bytes_read = 0;
            std::string result;
            while (InternetReadFile(
                h_connect,
                buffer,
                sizeof(buffer),
                &bytes_read)
                && bytes_read > 0
                ) {

                result.append(buffer, bytes_read);

            }

            InternetCloseHandle(h_connect);
            return result;
            
        }else {
#ifdef _MSC_VER
            std::cerr << "Failed to open URL: " << GetLastError() << std::endl;
#endif
        }
        InternetCloseHandle(h_internet);
    }
    else {
#ifdef _MSC_VER
        std::cerr << "Failed to initialize WinINet: " << GetLastError() << std::endl;
#endif
    }
    return "";

}

std::string Network::get_mac_address()
{
    std::string macAddress;

    // Buffer to store adapter information
    PIP_ADAPTER_INFO pAdapterInfo = nullptr;
    ULONG ulBufferSize = sizeof(IP_ADAPTER_INFO);
    pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(ulBufferSize));
    if (pAdapterInfo == nullptr) {
        return "";
    }

    // Retrieve adapter information
    if (GetAdaptersInfo(pAdapterInfo, &ulBufferSize) == ERROR_BUFFER_OVERFLOW) {
        free(pAdapterInfo);
        pAdapterInfo = reinterpret_cast<IP_ADAPTER_INFO*>(malloc(ulBufferSize));
        if (pAdapterInfo == nullptr) {
            return "";
        }
    }

    if (GetAdaptersInfo(pAdapterInfo, &ulBufferSize) == NO_ERROR) {
        PIP_ADAPTER_INFO pAdapter = pAdapterInfo;
        while (pAdapter) {
            if (pAdapter->Type == MIB_IF_TYPE_ETHERNET) { // Check if the adapter is Ethernet
                std::stringstream ss;
                for (UINT i = 0; i < pAdapter->AddressLength; i++) {
                    if (i == 0) {
                        ss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(pAdapter->Address[i]);
                    }
                    else {
                        ss << "-" << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << static_cast<int>(pAdapter->Address[i]);
                    }
                }
                macAddress = ss.str();
                break; // Found MAC address, no need to continue
            }
            pAdapter = pAdapter->Next;
        }
    }

    // Cleanup
    if (pAdapterInfo) {
        free(pAdapterInfo);
    }

    return macAddress;
}
