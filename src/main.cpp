#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <filesystem>
#include <preprocessor.h>

using namespace std;

int main(int argcount, char* arg[]) {

    if (argcount > 2) {
        cout << "[ tc Panic ]: Provide the file to compile as a command-line argument";
        return 1;
    }

    filesystem::path pfile = arg[1];
    ifstream file(pfile);
    if (!file.is_open()) {
        cout << "[ tc Panic ]:\nFailed to read file: "<<arg[1]<<endl;
        return 1;
    }

    stringstream filebuf;
    filebuf << file.rdbuf();
    string sfile = filebuf.str();
    if (sfile.empty()) {
        cout << "[ tc Panic ]:\nFailed to read content from the file: "<<arg[1]<<endl;
        return 1;
    }
    file.close();

    try {
        cout << parseIncludes(sfile, pfile.remove_filename());
    } catch (const runtime_error err) {
        cout << err.what();
    }
    
    
    return 0;
}
