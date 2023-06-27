#ifndef LOGGER_H
#define LOGGER_H

#include <string>

std::string getFormattedErrorString(const std::string message,
                            const std::string stage, 
                            const std::string file = "", 
                            const std::size_t errindex = 0);

std::string getPositionFromIndex(const std::string& str, size_t index);
#endif