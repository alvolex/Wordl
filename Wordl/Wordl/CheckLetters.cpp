#include "CheckLetters.h"

#include <iostream>
#include <string>
#include <unordered_map>

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"
#define OUT

enum class ForegroundColor : int {
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int {
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103
};




bool CheckLetters::CheckWord(std::string word, std::string playerGuess, OUT int& remainingTries)
{
    bool hasGuessedCorrectWord = true;
    std::pmr::unordered_map<char, int> letterCounter;
    
    if (playerGuess.length() == word.length())
    {
        //Calculat/check instances of letters
        letterCounter = MakeHashMapOfLetterCount(word);

        //Check letters
        for (int i = 0; i < word.length(); ++i)
        {
            //If the 'player' has written a word with multiples of one letter, we check if the word has more than one of that letter, otherwise we print the n-th instance of the letter as grey.
            bool letterIsValid = false;
            if (letterCounter[playerGuess[i]] > 0)
            {
                letterIsValid = true;
                letterCounter[playerGuess[i]]--;
            }
            
            if (std::tolower(playerGuess[i]) == std::tolower(word[i]) && letterIsValid)
            {
                std::cout << BACKGROUND(BackgroundColor::Green,playerGuess[i]);
            }                
            else if ((word.find(std::toupper(playerGuess[i])) != std::string::npos) || (word.find(std::tolower(playerGuess[i]))!= std::string::npos) && letterIsValid)
            {
                std::cout << BACKGROUND(BackgroundColor::BrightYellow,playerGuess[i]);
                hasGuessedCorrectWord = false;
            }
            else
            {
                std::cout << playerGuess[i];
                hasGuessedCorrectWord = false;
            }

            //todo remove this debug
            //std::cout << "Letter: " << playerGuess[i] << " Count: " << letterCounter[playerGuess[i]] << std::endl;
        }
        remainingTries--;
    }
    else
    {            
        std::cout << "Please type a " << word.length() << " letter word.";
        hasGuessedCorrectWord = false;
    }

    return hasGuessedCorrectWord;
}

std::pmr::unordered_map<char, int> CheckLetters::MakeHashMapOfLetterCount(std::string word)
{
    std::pmr::unordered_map<char, int> letterCounter;
    for (int i = 0; i < word.length(); ++i)
    {            
        if (letterCounter[word[i]]) continue; //No need to count letters of a character we've already counted
            
        int count = 0;            
        //Get amount of the current letter
        for (int x = 0; ((x = word.find(word[i], x)) != std::string::npos); ++x)
        {
            count++;
        }            
        //Populate hash table
        letterCounter[word[i]] = count;            
    }

    return letterCounter;
}
