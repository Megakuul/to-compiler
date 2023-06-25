#include <string>
#include <stdexcept>
#include <utility.h>

using namespace std;

string parseIncludes(string entryfile) {

  string incStatement = "justget::";

  size_t includePos = entryfile.find(incStatement);
  if (includePos != string::npos) {
    size_t sPos = includePos + incStatement.length();
    string* pathBuf = new string[0];

    for (size_t i = sPos; i < entryfile.length(); i++) {
      char *c = &entryfile[i];
      if (isspace(*c)) continue;

      if (!isalpha(*c) && *c != '.' && *c != '/' && *c != '\\') {
        getLinePosition()
        throw runtime_error("Illegal character at")
      } 
    }          
  } 

  entryfile.find("just get");
}