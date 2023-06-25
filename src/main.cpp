#include <iostream>
#include <fstream>
#include <string>
#include <preprocessor.h>

using namespace std;

int main(int argcount, char* arg[]) {

    if (argcount > 2) {
        cout << "[ tc Panic ]: Provide the file to compile as a command-line argument";
        return 1;
    }

   ifstream file(arg[1]);

    if (!file.is_open()) {
        cout << "[ tc Panic ]:\nFailed to read file: "<<arg[1]<<endl;
        return 1;
    }

    string sfile;
    if (!(file >> sfile)) {
        cout << "[ tc Panic ]:\nFailed to read content from the file: "<<arg[1]<<endl;
        return 1;
    }
    file.close();

    parseIncludes(sfile);
    

    return 0;
}
