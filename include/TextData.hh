//
// Created by Nikita on 05/11/2025.
//

#ifndef TEXTDATA_HH
#define TEXTDATA_HH
#include <iostream>
#include <string>
#include <fstream>
#include <cctype>

using namespace std;

class TextData {
private:
    string fileName;
    string text;
    int numberOfVowels;
    int numberOfConsonants;
    int numberOfLetters;
    int numberOfSentences;
    string longestWord;

    bool isLetter(char c) {
        c = tolower(c);
        return (c >= 'a' && c <= 'z');
    }

    bool isVowel(char c) {
        c = tolower(c);
        return (c == 'a' || c == 'e' || c == 'o' || c == 'u' || c == 'i');
    }

public:
    TextData(string fileName, string text) {
        this->fileName = fileName;
        this->text = text;

    }

    string getFilename() {
        return fileName;
    }

    string getText() {
        return text;
    }

    int getNumberOfVowels() {
        int numberOfVowels = 0;
        for (int i = 0; i < text.length(); i++) {
            if (isVowel(text[i])) {
                numberOfVowels++;
            }
        }
        return numberOfVowels;
    }

    int getNumberOfConsonants() {
        int numberOfConsonants = 0;
        for (int i = 0; i < text.length(); i++) {
            if (isLetter(text[i])) {
                if (!isVowel((text[i]))) {
                    numberOfConsonants++;
                }
            }
        }
        return numberOfConsonants;
    }

    int getNumberOfLetters() {
        numberOfLetters = 0;
        for (int i = 0; i < text.length(); i++) {
            if (isLetter(text[i])) {
                numberOfLetters++;
            }
        }
        return numberOfLetters;
    }

    int getNumberOfSentences() {
        numberOfSentences = 0;
        for (int i = 0; i < text.length(); i++) {
            if (text[i] == '\n' || text[i] == '.' || text[i] == '!' || text[i] == '?') {
                numberOfSentences++;
            }
        }
        return numberOfSentences;
    }

    string getLongestWord() {
        string current_word = "";
        int current_length = 0;
        string new_word = "";
        int new_length = 0;

        for (int i = 0; i < text.length(); i++) {
            char c = text[i];
            if (c != ' ' && c != '\n' && c != '\t' && c != '.' && c != ',' && c != '!' && c != '?') {
                new_word.push_back(c);
                new_length++;
            } else {
                if (new_length > current_length) {
                    current_word = new_word;
                    current_length = new_length;
                }
                new_word = "";
                new_length = 0;
            }
        }

        return current_word;
    }

};
#endif //TEXTDATA_HH
