#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <fstream>
#include <filesystem>
#include <logger.h>

using namespace std;

string parseIncludes(string entryfile, filesystem::path basePath, vector<string> &includedDependencies) {

  /**
   * Defines the string of the include statement
  */
  string incStatement = "justget::";

  /**
   * Defines the final return, it is initialized with the entryfile
   * so if no includes are found it will just return the entryfile
  */
  string fullBuf = entryfile;

  /**
   * Defines the position of the current include statement
  */
  size_t curIncludePos = entryfile.find(incStatement);

  while (curIncludePos != string::npos) {
    
    /**
     * Defines the position after the current include statement
    */
    size_t afterCurIncludePos = curIncludePos + incStatement.length();
    
    /**
     * Buffer for the include
    */
    string* includeBuf = new string;

    curIncludePos = entryfile.find(incStatement, curIncludePos + 1);

    for (size_t i = afterCurIncludePos; i < entryfile.length(); i++) {
      char *c = &entryfile[i];

      if (isspace(*c)) continue;

      if (*c == ';') break;

      if (!isalnum(*c) && *c != '.' && *c != '/' && *c != '\\') {
        throw runtime_error(getFormattedErrorString(
          "Include contains illegal character. Use only [.] [/] [\\], letters, or/and numbers.",
          "PREPROCESSOR",
          entryfile, i
        ));
      }

      *includeBuf += *c;
    }
    /**
     * Defines the path for the include (basePath + pathBuf)
    */
    filesystem::path incPath = basePath;
    incPath.append(*includeBuf);
    cout << incPath << endl;
    if (!filesystem::exists(incPath)) {
      throw runtime_error(getFormattedErrorString(
          "Invalid include: " + incPath.string() + 
          " \nInclude paths must be relative to the application entry point, not the current file.",
          "PREPROCESSOR"
      ));
    }

    // Check if the dependency is already loaded
    if (find(includedDependencies.begin(), includedDependencies.end(), incPath.filename().string()) 
        != includedDependencies.end()) {
        continue;
    }

    // Add the current dependency to the list
    includedDependencies.push_back(incPath.filename().string());


    /**
     * Defines a ifstream of the include file
    */
    ifstream ifsfile(incPath);

    if (!ifsfile.is_open()) {
      throw runtime_error(getFormattedErrorString(
        "Failed to read file: " + incPath.string(),
        "PREPROCESSOR"
      ));
    }

    /**
     * Buffer for the file
     * 
     * The purpose of this buffer is to write the whole ifstream into a single string
    */
    stringstream ssfilebuf;
    ssfilebuf << ifsfile.rdbuf();

    /**
     * Defines a string of the include file
    */
    string sfile = ssfilebuf.str();

    if (sfile.empty()) {
      throw runtime_error(getFormattedErrorString(
        "Failed to read contents of file: " + incPath.string(),
        "PREPROCESSOR"
      ));
    }
    ifsfile.close();

    fullBuf += parseIncludes(sfile, basePath, includedDependencies);
  } 

  return fullBuf;
}