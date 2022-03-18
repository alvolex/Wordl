#pragma once
#include <string>
#include <unordered_map>

#define OUT

class CheckLetters
{    
public:
    static void SetupAlphabet();    
    static bool CheckWord(std::string word, std::string playerGuess, OUT int& remainingTries, std::vector<char>& vec);

private:
    static void PrintColoredLetters(std::string playerGuess, std::unordered_map<int, int> letterColor);
    static std::unordered_map<char, std::tuple<int, std::vector<int>>> MakeHashMapOfLetterCount(std::string word);
    static void CreateAlphabeteVector(const std::string& alphabet, OUT std::vector<char>* vec);    
};
