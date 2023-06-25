#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <utility.h>

using namespace std;

// TODO: Create a Logger

string parseIncludes(string entryfile, filesystem::path basePath) {

  string incStatement = "justget::";

  size_t includePos = entryfile.find(incStatement);
  if (includePos != string::npos) {
    size_t sPos = includePos + incStatement.length();
    string* pathBuf = new string;

    for (size_t i = sPos; i < entryfile.length(); i++) {
      char *c = &entryfile[i];

      if (isspace(*c)) continue;

      if (*c == ';') break;

      if (!isalpha(*c) && *c != '.' && *c != '/' && *c != '\\') {
        string err = "[ Preprocessor Error ]:\nIllegal character at " + getPositionFromIndex(entryfile, sPos);
        throw runtime_error(err);
      }

      *pathBuf += *c;
    }
    
    ifstream file(basePath.append(*pathBuf));

    if (!file.is_open()) {
      throw runtime_error("[ Preprocessor Error ]:\nFailed to read file " + *pathBuf);
    }

    stringstream filebuf;
    filebuf << file.rdbuf();
    string sfile = filebuf.str();

    if (sfile.empty()) {
      throw runtime_error("[ Preprocessor Error ]:\nFailed to read content from " + *pathBuf);
    }
    file.close();

    // TODO: Recursively add all dependencies togheter 
  } 

  return "";
}