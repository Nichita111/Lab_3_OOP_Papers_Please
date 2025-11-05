//
// Created by Nikita on 05/11/2025.
//

#ifndef FILEREADER_HH
#define FILEREADER_HH
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

class FileReader{
public:
    string readFileIntoString(string path){
        string buffer = "";

        // 1. Declare an ifstream object and open the file
        ifstream inputFile(path);

        // 2. Check if the file was opened successfully
        if (!inputFile.is_open()) {
            cerr << "Error: Could not open the file." << endl;
        }

        // 3. Read the file content line by line
        string line;
        while (getline(inputFile, line)) {
            // Process each line as needed
            buffer.append(line);
        }

        // 4. Close the file stream
        inputFile.close();
        return buffer;
    }

};

#endif //FILEREADER_HH
