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

  /**
   * Defines the string of the include statement
  */
  string incStatement = "justget::";

  /**
   * Defines the final return, it is initialized with the entryfile
   * so if no includes are found it will just return the entryfile
  */
  string fullBuf = entryfile;

  // TODO Implement this feature
  /**
   * Holds all included dependencies to avoid duplicated includes
  */
  vector<string> includedDependencies;

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
     * Buffer for the path of the include
    */
    string* pathBuf = new string;

    curIncludePos = entryfile.find(incStatement, curIncludePos + 1);

    for (size_t i = afterCurIncludePos; i < entryfile.length(); i++) {
      char *c = &entryfile[i];

      if (isspace(*c)) continue;

      if (*c == ';') break;

      if (!isalnum(*c) && *c != '.' && *c != '/' && *c != '\\') {
        string err = "[ Preprocessor Error ]:\nIllegal character at " + getPositionFromIndex(entryfile, i);
        throw runtime_error(err);
      }

      *pathBuf += *c;
    }

    /**
     * Defines the path for the include (basePath + pathBuf)
    */
    filesystem::path incPath = basePath;
    incPath.append(*pathBuf);
    
    /**
     * Defines a ifstream of the include file
    */
    ifstream ifsfile(incPath);

    if (!ifsfile.is_open()) {
      throw runtime_error("[ Preprocessor Error ]:\nFailed to read file " + incPath.string());
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
      throw runtime_error("[ Preprocessor Error ]:\nFailed to read content from " + *pathBuf);
    }
    ifsfile.close();

    fullBuf += parseIncludes(sfile, basePath);
    includedDependencies.push_back(*pathBuf);
  } 

  return fullBuf;
}