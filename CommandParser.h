#ifndef COMMAND_PARSER_H
#define COMMAND_PARSER_H

#include <vector>
#include <string>
#include <sstream>

class CommandParser {
public:
    std::vector<std::string> parse(const std::string& input) {
        std::vector<std::string> tokens;
        std::stringstream ss(input);
        std::string token;
        while (ss >> token) {
            tokens.push_back(token);
        }
        return tokens;
    }
};

#endif // COMMAND_PARSER_H

