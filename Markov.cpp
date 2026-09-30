#include <iostream>
#include <fstream>
#include "Markov.h"
#include <string>
using namespace std;

string joinWords(const std::string words[], int startIndex, int count) {
    string result = "";
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            result += " ";
        }
        result += words[startIndex + i];
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

std::string getRandomSuffix(const std::string prefixes[], const std::string suffixes[],int chainSize, 
    std::string currentPrefix) {
        int matchCount = 0;
        for (int i = 0; i < chainSize; i++) {
            if (prefixes[i] == currentPrefix) {
                matchCount++;
            }
        }
        if (matchCount == 0) {
            return "";
        }

        int pick = std::rand() % matchCount;
        int secondCount = 0;
        for (int i = 0; i < chainSize; i++) {
            
            if (prefixes[i] == currentPrefix) {
                if (secondCount == pick) {
                    return suffixes[i];
                }
                secondCount++;
            }
        }
        return "";
    }

std::string getRandomPrefix(const std::string prefixes[], int chainSize) {
    if (chainSize <= 0) return "";
    int index = rand() % chainSize;
    return prefixes[index];
}
