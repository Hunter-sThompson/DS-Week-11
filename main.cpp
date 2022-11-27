#include <iostream>
#include <map>
#include <string>
#include <cstring>
#include <vector>
#include <cctype>
#include <utility>
#include <streambuf>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <codecvt>

using namespace std;

// Basic readfile using istreambuf
string readfile(char *fname) {

    ifstream t(fname);
    string str((istreambuf_iterator<char>(t)),
                istreambuf_iterator<char>());
    
    return str;
}

/*
wstring readwfile(char *fname) {
    wifstream wif(fname);
    wif.imbue(locale(locale::empty(), new codecvt_utf8<wchar_t>));
    wstringstream wss;
    wss << wif.rdbuf();
    return wss.str();
}
*/

// Gets max value from map, returns as pair. 
pair<char, int> frequentChar(map<char, int> freqmap) {

    // Default values are - and 0
    pair<char, int> mostFrequent = make_pair('-', 0);
    map<char, int>::iterator it;

    // Simple maxelement, just checking each one by one, to find largest
    for (it = freqmap.begin(); it != freqmap.end(); ++it) {

        if (it->second > mostFrequent.second) {
            mostFrequent = make_pair(it->first, it->second);
        }
    }
    return mostFrequent;
}

// Writes the file as output.tsv
void write_file(vector<string> contents) {

    fstream fs;
    fs.open("output.tsv", ios_base::out);
    vector<string>::iterator it;

    for (it = contents.begin(); it != contents.end(); it++) {
        fs << *it << endl;
        cout << *it << endl;
    }
    cout << "Finished exporting output.tsv" << endl;
}

int main(int argc, char **argv) {

    string contents;

    // Switch case statement for argument check
    switch (argc) {
        case 2:
            contents = readfile(argv[1]);
            break;
        case 3:

            if (strcmp("-l", argv[1]) != 0) {
                cout << "Usage: ./main.exe [-l] inputFile.txt" << endl;
                exit(-1);
            }
            contents = readfile(argv[2]);
            // Makes all chars in contents lowercase 
            transform(contents.begin(), contents.end(), contents.begin(), [](unsigned char c){ return tolower(c); });
            break;

        default:     
            cout << "Usage: ./main.exe [-l] inputFile.txt" << endl;
            exit(-1);
    }

    // Stores each sentence in a vector<string>
    vector<string> sentences;
    string sentence;
    stringstream ss(contents);

    // Uses stringstream to extract contents line by line from file, into vector with '\n' as divider
    while (getline(ss, sentence, '\n')) {
        sentences.push_back(sentence);
    }

    // Stores char frequencies for each sentence, as string
    vector<string> frequencies;

    int i;
    // Iterate over sentences
    for (auto sentence: sentences) {
        
        // Creates a map key being a char, and int being the amount of times it appeared in the sentence
        map<char, int> freqmap; 

        // Loops through the sentence
        for (i = 0; i < sentence.size(); i++) {

            // Continues over whitespace chars
            if (isspace(sentence[i]) != 0) { continue; }

            // Checks if the char exists as a key in the map, if not, then the char is inserted with value of 1
            if (!(freqmap.count(sentence[i]) > 0)) {
                freqmap.insert({sentence[i], 1});

            // If it does exist, then the value is incremented
            } else {
                freqmap[sentence[i]]++;
            }
        }
        // To find the most frequent characte
        pair<char, int> freqchar = frequentChar(freqmap);
        // Converting types and appending to vector
        string cs(1, freqchar.first);
        string fin = cs + "\t" + to_string(freqchar.second);

        frequencies.push_back(fin);
    }

    write_file(frequencies);

    cout << "Done" << endl;
    return 0;
}
