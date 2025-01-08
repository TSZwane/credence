#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <string>

class Encryption {
public:
    std::string encrypt(const std::string& data) {
        std::string encrypted = data;
        for (char& c : encrypted) c += 3; // Simple Caesar cipher
        return encrypted;
    }

    std::string decrypt(const std::string& data) {
        std::string decrypted = data;
        for (char& c : decrypted) c -= 3; // Reverse Caesar cipher
        return decrypted;
    }
};

#endif // ENCRYPTION_H

