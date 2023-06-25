#include <string>
#include <iostream>
#include <stdexcept>
#include <utility.h>

using namespace std;

string parseIncludes(string entryfile) {

  string incStatement = "justget::";

  size_t includePos = entryfile.find(incStatement);
  if (includePos != string::npos) {
    size_t sPos = includePos + incStatement.length();
    string* pathBuf = new string;

    for (size_t i = sPos; i < entryfile.length(); i++) {
      char *c = &entryfile[i];
      cout << *c << endl;
      if (isspace(*c)) continue;

      if (*c == '\n') break;

      if (!isalpha(*c) && *c != '.' && *c != '/' && *c != '\\') {
        string err = "[ Preprocessor Error ]:\nIllegal character at " + getPositionFromIndex(entryfile, sPos);
        throw runtime_error(err);
      }

      *pathBuf += *c;
    }
    cout << *pathBuf << endl;     
  } 

  return "";
}