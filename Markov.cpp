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

int buildMarkovChain(const std::string words[], int numWords, int order, std::string prefixes[], 
    std::string suffixes[], int maxChainSize) {
        if (order > 3 || order < 1 || numWords <= order || maxChainSize <= 0) {
            return 0;
        } else {
            int count = 0;
            for (int i = 0; i < numWords - order && count < maxChainSize; i++) {
                std::string prefix = joinWords(words, i, order);
                std::string suffix = words[i + order];

                prefixes[count] = prefix;
                suffixes[count] = suffix;
                count++;
            }
            return count;
        }
    }
