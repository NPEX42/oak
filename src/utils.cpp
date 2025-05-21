#include <oak/utils.hpp>

#include <fstream>
#include <sstream>
#include <iostream>

namespace oak {
    std::string ReadString(const std::string& filepath) {

        // Open the file using ifstream
        std::ifstream file(filepath);

        // confirm file opening
        if (!file.is_open()) {
            // print error message and return
            std::cerr << "Failed to open file: " << filepath << std::endl;

            return nullptr;
        }

        std::stringstream buffer;
        buffer << file.rdbuf();

        // Close the file
        file.close();
        return buffer.str();
    }
}