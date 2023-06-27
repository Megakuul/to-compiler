#include <iostream>
#include <sstream>
#include <string>
#include <logger.h>

/**
 * This function will return a formatted error string
 * 
 * The function is used to give an formated error message
 * 
 * @param message error message
 * @param stage stage of the compiler [PREPROCESSOR/LEXER/PARSER]
 * @param file current file
 * @param errindex position of the error inside the file
*/
std::string getFormattedErrorString(const std::string message,
                            const std::string stage, 
                            const std::string file, 
                            const std::size_t errindex) {
    std::ostringstream oss;
    oss << "[ " << stage << " PANIC ]:\n"
        << message << "\n"
        << (file.empty() ? "" : getPositionFromIndex(file, errindex)) << std::endl;
    return oss.str();
}

/**
 * This function will return the position of the index
 * 
 * The position is formattet like: '[ line: 5, character: 7 ]'
 * 
 * The function is used to give an exact output if an error occurs during compilation
 * 
 * @param str content of the file
 * @param index index of the error
*/
std::string getPositionFromIndex(const std::string& str, size_t index) {
    size_t linebuf = 1;
    size_t charbuf = 1;

    for (size_t i = 0; i < index; i++) {
        if (str[i] == '\n') {
            charbuf = 0;
            linebuf++;
        } else {
            charbuf++;
        }
    }

    std::ostringstream output;
    output << "( line: "<<linebuf<<", character: "<<charbuf<<" )";

    return output.str();
}