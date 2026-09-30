#include <iostream>
#include <fstream>
#include "Markov.h"
#include <string>
using namespace std;

string joinWords(const string words[], int startIndex, int count) {
    string result = "";
    for (int i = 0; i < count; i++) {
        if (i > 0) {
            result += " ";
        }
        result += words[startIndex + i];
    }
    return result;

}

int readWordsFromFile(string filename, string words[], int maxWords) {
    ifstream inputFile(filename);
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

int buildMarkovChain(const string words[], int numWords, int order, string prefixes[], 
    string suffixes[], int maxChainSize) {
        if (order > 3 || order < 1 || numWords <= order || maxChainSize <= 0) {
            return 0;
        } else {
            int count = 0;
            for (int i = 0; i < numWords - order && count < maxChainSize; i++) {
                string prefix = joinWords(words, i, order);
                string suffix = words[i + order];

                prefixes[count] = prefix;
                suffixes[count] = suffix;
                count++;
            }
            return count;
        }
    }

string getRandomSuffix(const string prefixes[], const string suffixes[],int chainSize, 
    string currentPrefix) {
        int matchCount = 0;
        for (int i = 0; i < chainSize; i++) {
            if (prefixes[i] == currentPrefix) {
                matchCount++;
            }
        }
        if (matchCount == 0) {
            return "";
        }

        int pick = rand() % matchCount;
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

string getRandomPrefix(const string prefixes[], int chainSize) {
    if (chainSize <= 0) return "";
    int index = rand() % chainSize;
    return prefixes[index];
}

string generateText(const string prefixes[], const string suffixes[],int chainSize, int order, 
    int numWords) {
        if (chainSize <= 0 || order < 1 || order > 3 || numWords < order) return "";
        string currentPrefix = getRandomPrefix(prefixes, chainSize);
        string result = currentPrefix;

        string currentWords[3]; // supports the validated orders 1, 2, and 3
        int wordIndex = 0;                                                                                                                                                                 
        string temp = "";
        for (int i = 0; i < currentPrefix.length(); i++) {                                                                                                                                 
            if (currentPrefix[i] == ' ') {     // ' '                                                                                                                                            
                currentWords[wordIndex] = temp;                                                                                                                                            
                wordIndex++;                                                                                                                                                               
                temp = "";                 
            } else {                                                                                                                                                                       
                temp += currentPrefix[i];  
            }
        }
        currentWords[wordIndex] = temp; // don't forget the last word

        
        for (int i = 0; i < numWords - order; i++) {
            string newWord = getRandomSuffix(prefixes, suffixes, chainSize, currentPrefix);
            if (newWord == "") {
                break;
            }
            result += (" " + newWord);

            for (int j = 0; j < order - 1; j++) {
                currentWords[j] = currentWords[j + 1];
            }
            currentWords[order - 1] = newWord;
            currentPrefix = joinWords(currentWords, 0, order);
        }
        return result;
    }
