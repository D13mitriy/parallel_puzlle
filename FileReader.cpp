#include "FileReader.h"
#include <fstream>
#include <iostream>
#include <algorithm>
#include <stdexcept>

FileReader* FileReader::instance = nullptr;

FileReader* FileReader::getInstance() {
    if (!instance) {
        instance = new FileReader();
    }
    return instance;
}

std::vector<std::string> FileReader::readFile(const std::string& filename) {
    std::vector<std::string> numbers;
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw std::runtime_error("Error: Could not open file " + filename);
    }

    std::string line;
    while (std::getline(file, line)) {
        if (!line.empty() && std::all_of(line.begin(), line.end(), ::isdigit)) {
            numbers.push_back(line);
        } else if (!line.empty()) {
            std::cerr << "Warning: Skipping invalid line (not numeric): " << line << std::endl;
        }
    }

    file.close();
    return numbers;
}
