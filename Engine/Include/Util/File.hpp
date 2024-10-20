#pragma once

#include <Util/Common.hpp>
#include <fstream>
#include <sstream>

namespace blox
{
    class File
    {
    public:
        static std::string ToString(const std::string& path)
        {
            // Open the file in input mode
            std::ifstream fileStream(path);
            if (!fileStream)
                throw std::runtime_error("[Error] Could not open file: " + path);

            // Use a stringstream to read the file contents
            std::stringstream buffer;
            buffer << fileStream.rdbuf();

            // Return the contents of the file as a string
            return buffer.str();
        }
    };
}