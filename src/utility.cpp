#include <iostream>
#include <fstream>
#include <string>

void getPosition(const std::string& str, size_t index, size_t& line, size_t& charPos) {
    std::ifstream file(str);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + str);
    }

    std::string lineContent;
    size_t currentIndex = 0;
    line = 1;

    while (std::getline(file, lineContent)) {
        size_t lineLength = lineContent.length();
        if (currentIndex + lineLength >= index) {
            charPos = index - currentIndex;
            return;
        }
        currentIndex += lineLength + 1;  // +1 to account for the line break character
        line++;
    }

    // If the desired index is beyond the end of the file
    throw std::out_of_range("Index is beyond the end of the file");
}