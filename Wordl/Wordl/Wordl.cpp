#include <iostream>
#include <unordered_map>
#include <unordered_set>

#include "CheckLetters.h"
#include "GetWordFromFile.h"

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

void GameOver(bool hasWon, std::string str);
void CreateAlphabeteVector(const std::string& alphabet, std::vector<char>* vec);


int main()
{
    //Setup alphabet string
    std::string const alphabet = "abcdefghijklmnopqrstuvwxyz";
    std::vector<char> remainingLetters;
    CreateAlphabeteVector(alphabet, OUT &remainingLetters);
    
    //Get a word
    std::string word = GetWordFromFile::GetWordToGuess();
    std::string playerGuess = "";
    
    int remainingTries = 6;
    bool hasWon = false;       

    std::cout << "Hello! " /*<< "Debug text || Word To Guess: " << word */<< std::endl;

    //Loop while we still have tries left
    while (remainingTries > 0)
    {
        std::cout << std::endl << "Remaining attempts: " << remainingTries <<" | Type your guess:" << std::endl;
        std::cin >> playerGuess;
        
        hasWon = CheckLetters::CheckWord(word, playerGuess, OUT remainingTries,remainingLetters);

        if (hasWon) break;
    }

    GameOver(hasWon, word);

    //Wait for any type of input before closing the app
    std::cin >> playerGuess;
    return 0;
}

void CreateAlphabeteVector(const std::string& alphabet, std::vector<char>* vec)
{
    for (int i = 0; i < alphabet.length(); ++i)
    {
        vec->push_back(std::toupper(alphabet[i]));
    }
}

void GameOver(bool hasWon, std::string word)
{
    if (!hasWon)
    {
        std::cout << std::endl<< BACKGROUND(BackgroundColor::Red,"You lost, better luck next time! The correct word was: " << word << std::endl);
    }
    else
    {
        std::cout << std::endl<< BACKGROUND(BackgroundColor::BrightGreen,"Congratulations, you guessed the correct word!") << std::endl;
    }
}


