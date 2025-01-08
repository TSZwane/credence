#ifndef AUTHENTICATION_H
#define AUTHENTICATION_H

#include <cstdlib>
#include <unistd.h>
#include <sys/types.h>

class Authentication {
public:
    static bool checkSudo() {
        return geteuid() == 0;
    }
};

#endif // AUTHENTICATION_H

