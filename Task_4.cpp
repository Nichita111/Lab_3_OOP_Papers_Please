#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "TextData.hh"
#include "FileReader.hh"

using namespace std;

int main(int argc, char* argv[]) {
    // need at least one pair: <name> <full_path>
    if (argc < 3 || ((argc - 1) % 2) != 0) {
        cerr << "Usage: " << argv[0]
             << " <name1> <full_path1> <name2> <full_path2> ...\n";
        return 1;
    }

    FileReader file;
    vector<TextData> datas;

    for (int i = 1; i < argc; i += 2) {
        string name = argv[i];        // logical name you want to display
        string path = argv[i + 1];    // FULL path to the file

        string text = file.readFileIntoString(path);

        TextData data(name, text);
        datas.push_back(data);

        cout << data.getFilename() << endl
             << data.getText() << endl
             << data.getNumberOfVowels() << endl
             << data.getNumberOfConsonants() << endl
             << data.getNumberOfLetters() << endl
             << data.getNumberOfSentences() << endl
             << data.getLongestWord() << endl;

        if (i + 2 < argc) cout << "\n\n";
    }

    return 0;
}
