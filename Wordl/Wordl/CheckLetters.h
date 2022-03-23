#pragma once
#include <string>
#include <unordered_map>
#include <unordered_map>
#include <unordered_map>

#define OUT // feedback: an interesting way of marking outgoing arguments :) I didn't see such usage of define macro before. Usually I just change the name
            // of the argument itself, like remainingTries -> outRemainingTries. 

enum LetterColor
{
    Green,
    Yellow,
    Grey,
    Debug
};

class CheckLetters
{    
public:
    static void SetupAlphabet();    // feedback: doesn't seem like this function implemented anywhere?
    // feedback: string references could be used here to avoid copying, as you did in CreateAlphabeteVector for example.
    // OUT macro and different names of the last arg in declaration and definition of the function makes it confusing
    static bool CheckWord(std::string word, std::string playerGuess, OUT int& remainingTries, std::vector<char>& vec);

private:
    // feedback: same here, refs for string and map args are preferred here. Map can potentially be pretty heavy object to copy
    static void PrintColoredLetters(::std::string playerGuess, std::unordered_map<int, LetterColor> letterColor);
    static std::unordered_map<char, std::tuple<int, std::vector<int>>> MakeHashMapOfLetterCount(std::string word);
    static void CreateAlphabeteVector(const std::string& alphabet, OUT std::vector<char>* vec);    
};
