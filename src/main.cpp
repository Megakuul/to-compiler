#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argcount, char* arg[]) {

    if (argcount > 2) {
        cout << "[ tc Panic ]: Provide the file to compile as a command-line argument";
        return 1;
    }

   ifstream file(arg[1]);

    if (!file.is_open()) {
        cout << "[ tc Panic ]: Failed to read file: "<<arg[1]<<endl;
        return 1;
    }

    string line;
    while (std::getline(file, line)) {
        cout << line << endl;
    }

    file.close();

    return 0;
}
