#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <streambuf>
#include <algorithm>
#include <fstream>

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

    string contents;

    switch (argc) {
        case 2:
            contents = readfile(argv[1]);
            break;
        case 3:

            if (strcmp("-l", argv[1]) != 0) {
                cout << "Usage: ./main.exe [-l] inputFile.txt" << endl;
                exit(-1);
            }
            contents = tolower(readfile(argv[2]));
            break;

        default:     
            cout << "Usage: ./main.exe [-l] inputFile.txt" << endl;
            exit(-1);
    }

    vector<string> sentences;
    string sentence;
    stringstream ss(contents);
    while (getline(ss, sentence, '\n')) {
        sentences.push_back(sentence);
    }

    vecotr<string> frequencies;
    int i;
    for (auto sentence: sentences) {
        
        vector<char> strchars;

        for (i = 0; i < sentence.size(); i++) {
            if (find(strchars.begin(), strchars.end(), sentence[i]) == strchars.end()){
                strchars.push_back(sentence[i]);
            }

            

        }


    }
    cout << "Here's the contents of the file" << endl;
    cout << contents << endl;


    return 0;
}
