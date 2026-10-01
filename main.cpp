#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Markov.h"

int main() {
    std::srand(std::time(0));

    std::string filename;
    int order;
    int numWords;
    const int MAX_WORDS = 5000;
    std::cout << "Enter filename: ";
    std::cin >> filename;
    std::cout << "Enter order: ";
    std::cin >> order;
    while (order < 1 || order > 3) {
        std::cout << "Invalid order, please input an integer between 1 and 3: ";
        std::cin >> order;
    }
    std::cout << "Enter maximum number of words: ";
    std::cin >> numWords;
    while (numWords < order || numWords >= MAX_WORDS) {
        std::cout << "Invalid number of words, at most " << MAX_WORDS << " words were used and ";
        std::cout << order + 1 << " words are needed: ";
        std::cin >> numWords;
    }
    
    std::ifstream inputFile(filename);
    if (!inputFile.is_open()) {
        std::cout << "Error opening file" << std::endl;
        return -1;
    }

    std::string testWords[] = {"the", "cat", "sat", "down"};
    std::cout << joinWords(testWords, 0, 2) << std::endl;  // Should print: the cat
    std::cout << joinWords(testWords, 1, 3) << std::endl;  // Should print: cat sat down

    std::string words[MAX_WORDS];
    int count = readWordsFromFile(filename, words, MAX_WORDS);
    std::cout << "Read " << count << " words" << std::endl;
    for (int i = 0; i < 10 && i < count; i++) {
        std::cout << words[i] << std::endl;
    }

    std::string prefixes[MAX_WORDS], suffixes[MAX_WORDS];
    int chainSize = buildMarkovChain(words, count, 1, prefixes, suffixes, MAX_WORDS);
    if (chainSize <= 0) {
        std::cout << "Could not build Markov chain." << std::endl;
        return 1;
    }
    for (int i = 0; i < 20 && i < chainSize; i++) {
        std::cout << "[" << prefixes[i] << "] -> [" << suffixes[i] << "]" << std::endl;
    }


    for (int i = 0; i < 10; i++) {
        std::cout << getRandomSuffix(prefixes, suffixes, chainSize, "the") << std::endl;
    }

    for (int i = 0; i < 5; i++) {
        std::cout << getRandomPrefix(prefixes, chainSize) << std::endl;
    }

    std::string output = generateText(prefixes, suffixes, chainSize, order, numWords);
    std::istringstream iss(output);
    std::string white;
    int generated = 0;
    while (iss >> white) {
        generated++;
    }

    std::cout << "Generated " << generated << " words out of " << numWords << " words: " << output << std::endl;
    if (generated < numWords) {
        std::cout << "Dead end, no successor for ";
    }
}