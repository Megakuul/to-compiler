#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <string>
#include <filesystem>

    std::string parseIncludes(std::string entryfile, std::filesystem::path basePath);
#endif
