#pragma once
#include <string>
#include <unordered_map>

#define OUT

class CheckLetters
{
public:
    static bool CheckWord(std::string word, std::string playerGuess, OUT int& remainingTries);

private:
    static std::pmr::unordered_map<char, int> MakeHashMapOfLetterCount(std::string word);
};
