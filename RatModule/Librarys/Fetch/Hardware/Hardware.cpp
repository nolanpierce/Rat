#include "Hardware.h"

std::string Hardware::id()
{
    std::string hardwareID;

    // Initialize COM
    HRESULT hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);
    if (SUCCEEDED(hr)) {
        // Initialize security
        hr = CoInitializeSecurity(
            NULL,
            -1,                          // COM authentication
            NULL,                        // Authentication services
            NULL,                        // Reserved
            RPC_C_AUTHN_LEVEL_DEFAULT,   // Default authentication 
            RPC_C_IMP_LEVEL_IMPERSONATE, // Default Impersonation  
            NULL,                        // Authentication info
            EOAC_NONE,                   // Additional capabilities 
            NULL                         // Reserved
        );

        if (SUCCEEDED(hr)) {
            // Create the WMI locator
            IWbemLocator* pLoc = nullptr;
            hr = CoCreateInstance(
                CLSID_WbemLocator,
                0,
                CLSCTX_INPROC_SERVER,
                IID_IWbemLocator, (LPVOID*)&pLoc
            );

            if (SUCCEEDED(hr)) {
                // Connect to the root\cimv2 namespace
                IWbemServices* pSvc = nullptr;
                hr = pLoc->ConnectServer(
                    _bstr_t(L"ROOT\\CIMV2"),
                    NULL,
                    NULL,
                    0,
                    NULL,
                    0,
                    0,
                    &pSvc
                );

                if (SUCCEEDED(hr)) {
                    // Set the authentication information
                    hr = CoSetProxyBlanket(
                        pSvc,
                        RPC_C_AUTHN_WINNT,
                        RPC_C_AUTHZ_NONE,
                        NULL,
                        RPC_C_AUTHN_LEVEL_CALL,
                        RPC_C_IMP_LEVEL_IMPERSONATE,
                        NULL,
                        EOAC_NONE
                    );

                    if (SUCCEEDED(hr)) {
                        // Query for hardware identifier
                        IEnumWbemClassObject* pEnumerator = nullptr;
                        hr = pSvc->ExecQuery(
                            _bstr_t("WQL"),
                            _bstr_t("SELECT * FROM Win32_ComputerSystemProduct"),
                            WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY,
                            NULL,
                            &pEnumerator
                        );

                        if (SUCCEEDED(hr)) {
                            // Get the hardware ID
                            IWbemClassObject* pclsObj = nullptr;
                            ULONG uReturn = 0;
                            hr = pEnumerator->Next(WBEM_INFINITE, 1, &pclsObj, &uReturn);
                            if (uReturn != 0) {
                                VARIANT vtProp;
                                hr = pclsObj->Get(L"UUID", 0, &vtProp, 0, 0);
                                if (SUCCEEDED(hr)) {
                                    hardwareID = _com_util::ConvertBSTRToString(vtProp.bstrVal);
                                    VariantClear(&vtProp);
                                }
                                pclsObj->Release();
                            }
                            pEnumerator->Release();
                        }
                    }
                    pSvc->Release();
                }
                pLoc->Release();
            }
            CoUninitialize();
        }
    }
    return hardwareID;
}
