#include <iostream>
#include <fstream>
#include "Markov.h"
#include <string>
using namespace std;

string joinWords(const std::string words[], int startIndex, int count) {
    string result = "";
    for (int i = 0; i < count; i++) {
        result += words[startIndex + i]; // add spaces?
        result += " ";
    }
    return result;

}

int readWordsFromFile(std::string filename, std::string words[], int maxWords) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        return -1;
    } else {
        int counter = 0;
        while (counter < maxWords && inputFile >> words[counter]) {
            counter++;
        }
        inputFile.close();
        return counter;
    }
}