#include <iostream>
#include <string>
#include "CommandParser.h"
#include "Authentication.h"
#include "DatabaseHandler.h"
#include "Encryption.h"

int main() {
    if (!Authentication::checkSudo()) {
        std::cerr << "Error: Sudo privileges are required.\n";
        return 1;
    }

    CommandParser parser;
    DatabaseHandler db("password_keeper.db");
    Encryption encryptor;

    while (true) {
        std::string command;
        std::cout << "> ";
        std::getline(std::cin, command);

        auto parsed = parser.parse(command);
        if (parsed.empty()) continue;

        std::string action = parsed[0];
        if (action == "exit") {
            break;
        } else if (action == "list") {
            auto credentials = db.listCredentials();
            for (const auto& cred : credentials) {
                std::cout << "App: " << cred.appName << ", Username: " 
                          << cred.username << ", Password: "
                          << encryptor.decrypt(cred.password) << "\n";
            }
        } else if (action == "add") {
            if (parsed.size() < 4) {
                std::cerr << "Usage: add <app_name> <username> <password>\n";
                continue;
            }
            std::string appName = parsed[1], username = parsed[2], password = parsed[3];
            db.addCredential(appName, username, encryptor.encrypt(password));
        } else if (action == "remove") {
            if (parsed.size() < 2) {
                std::cerr << "Usage: remove <app_name>\n";
                continue;
            }
            db.removeCredential(parsed[1]);
        } else {
            std::cerr << "Unknown command.\n";
        }
    }

    return 0;
}

