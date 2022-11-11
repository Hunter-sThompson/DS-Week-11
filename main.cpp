#include <iostream>

using namespace std;

string readfile(char *fname) {

    ifstream t(fname);
    string str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());
    
    cout << "here is the str from readfile" << endl;
    cout << str << endl;
    
    return str;
}

int main(int argc, char **argv) {


    cout << "Hello World!" << endl;
    return 0;
}
