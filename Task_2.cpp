#include <iostream>
#include <string>
#include <fstream>
#include <cctype>
#include "include/TextData.hh"
#include "include/FileReader.hh"

using namespace std;


int main(int argc, char* argv[]){

    if (argc < 3) {
        cerr << "Usage: " << argv[0] << " <name> <path-to-text-file>\n";
        return 1;
    }
    string name = argv[1];
    string path = argv[2];


  FileReader file;
  auto text = file.readFileIntoString(path);
    //cout << text;

    TextData data(name, text);
    cout <<data.getFilename() << endl<< data.getText() << endl << data.getNumberOfVowels() << endl << data.getNumberOfConsonants() << endl << data.getNumberOfLetters() << endl << data.getNumberOfSentences() << endl << data.getLongestWord();
    return 0;
}
