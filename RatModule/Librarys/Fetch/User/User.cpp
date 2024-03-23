#include "User.h"

std::string User::get_account_name() const
{
    TCHAR szBuffer[UNLEN + 1];
    DWORD dwSize = UNLEN + 1;
    if (GetUserName(szBuffer, &dwSize)) {
        return std::string(szBuffer);
    }
    else {
        return "";
    }
}

std::string User::get_computer_name() const
{
    TCHAR szBuffer[MAX_COMPUTERNAME_LENGTH + 1];
    DWORD dwSize = MAX_COMPUTERNAME_LENGTH + 1;
    if (GetComputerName(szBuffer, &dwSize)) {
        return std::string(szBuffer);
    }
    else {
        return "";
    }
}
