#ifndef FILEREADER_H
#define FILEREADER_H

#include <string>
#include <vector>

class FileReader {
public:
    static FileReader* getInstance();                     // Singleton instance accessor
    std::vector<std::string> readFile(const std::string& filename); // Reads numbers from a file

private:
    static FileReader* instance;
    FileReader() {} // Private constructor for Singleton
};

#endif // FILEREADER_H
