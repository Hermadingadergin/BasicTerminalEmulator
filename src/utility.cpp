#include "utility.h"
#include <string>
#include <sstream>

// Converts vector of strings to vector of char* (C-style strings)
std::vector<char*> castArgs(const std::vector<std::string>& cmd)
{
    std::vector<char*> result;
    for (const auto& s : cmd)
    {
        result.push_back(const_cast<char*>(s.c_str()));
    }
    result.push_back(nullptr);
    return result;
}

// Converts a command string to a vector of words
std::vector<std::string> cmd2vec(const std::string& command, char delimiter = ' ')
{
    std::vector<std::string> result;
    std::istringstream iss(command);
    std::string cmd_vec;
    while (std::getline(iss, cmd_vec, delimiter))
    {
        if (!cmd_vec.empty())
        {
            result.push_back(cmd_vec);
        }
    }
    return result;
}