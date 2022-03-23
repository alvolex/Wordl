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
void SetupGame(std::vector<char>& remainingLetters, std::string& word, std::string& playerGuess, int& remainingTries, bool& hasWon);

int main()
{
    std::vector<char> remainingLetters;
    std::string word;
    std::string playerGuess;
    int remainingTries;
    bool hasWon;
    std::string playerInput;
    
    SetupGame(remainingLetters, word, playerGuess, remainingTries, hasWon);

    std::cout << "Hello! " /*<< "Debug text || Word To Guess: " << word */<< std::endl;

    //Loop while we still have tries left
    bool playAgain = true;
    while (playAgain)
    {        
        while (remainingTries > 0)
        {
            std::cout << std::endl << "Remaining attempts: " << remainingTries <<" | Type your guess:" << std::endl;
            std::cin >> playerGuess;
        
            hasWon = CheckLetters::CheckWord(word, playerGuess, OUT remainingTries,remainingLetters);

            if (hasWon) break;
        }

        GameOver(hasWon, word);

        std::cout << "Do you wish to play again? Write 'Y', otherwise write anything else.." << std::endl;
        std::cin >> playerInput;

        if (playerInput.length() == 1 && std::toupper(playerInput[0]) == 'Y')
        {
            playAgain = true;
            SetupGame(remainingLetters, word, playerGuess, remainingTries, hasWon);
        }
        else
        {
            playAgain = false;
        }
    }
    return 0;
}

void SetupGame(std::vector<char>& remainingLetters, std::string& word, std::string& playerGuess, int& remainingTries, bool& hasWon)
{
    //Setup alphabet string
    std::string const alphabet = "abcdefghijklmnopqrstuvwxyz";
    CreateAlphabeteVector(alphabet, OUT &remainingLetters);

    word = GetWordFromFile::GetWordToGuess();
    playerGuess = "";

    remainingTries = 6;
    hasWon = false;
}

void CreateAlphabeteVector(const std::string& alphabet, std::vector<char>* vec)
{
    // feedback: not sure I understand the purpose of this function. If you needed an array of alphabet letters you could just create it statically?
    // The further manipulations on this array in CheckLetters::CheckWord are also unclear for me. Feels like it should be easier way to achieve the goal.
    vec->clear();
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


