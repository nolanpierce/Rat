#ifndef USERINFO
#define USERINFO
#include <Windows.h>
#include <iostream>
#include <Lmcons.h> // For UNLEN constant
#include <tchar.h>

class User {
public:

    std::string get_account_name() const;

    std::string get_computer_name() const;

    // going to add get microsoft email associated with user
    std::string microsoft_email() const;
};

#endif
