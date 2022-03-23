#include "CheckLetters.h"

#include <iostream>
#include <string>
#include <unordered_map>

#define FOREGROUND(color, text) "\x1B[" << static_cast<int>(color) << "m" << text << "\033[0m"
#define BACKGROUND(color, text) "\033[3;42;" << static_cast<int>(color) << "m" << text << "\033[0m"
#define OUT

enum class ForegroundColor : int
{
    Red = 31,
    Green = 32,
    Yellow = 33,
    BrightRed = 91,
    BrightGreen = 92,
    BrightYellow = 93
};

enum class BackgroundColor : int
{
    Red = 41,
    Green = 42,
    Yellow = 43,
    BrightRed = 101,
    BrightGreen = 102,
    BrightYellow = 103,
    None
};

enum TupleHelper
{
    Count,
    Indices
};


bool CheckLetters::CheckWord(std::string word, std::string playerGuess, int& remainingTries,std::vector<char>& remainingLetters)
{
    bool hasGuessedCorrectWord = true;

    //Letter, tuple <count, indices>
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounterInWordToGuess;
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounterInPlayerGuess;

    //index + green/yellow/nothing
    std::unordered_map<int, LetterColor> letterColor;
    std::vector<int> nonGreenIndex;

    if (playerGuess.length() == word.length())
    {
        //Calculate/check instances of letters
        letterCounterInWordToGuess = MakeHashMapOfLetterCount(word);
        letterCounterInPlayerGuess = MakeHashMapOfLetterCount(playerGuess);

        //Check green letters        
        for (int i = 0; i < word.length(); i++)
        {
            //Remove current letter from available letters
            remainingLetters.erase(
                std::remove(remainingLetters.begin(), remainingLetters.end(), std::toupper(playerGuess[i])),
                remainingLetters.end());

            bool caseInsensitiveCompare = std::to_string(std::tolower(playerGuess[i])) == std::to_string(
                std::tolower(word[i]));

            if (caseInsensitiveCompare)
            {
                letterColor[i] = Green;
                std::get<Count>(letterCounterInPlayerGuess[std::toupper(playerGuess[i])])--;
                std::get<Count>(letterCounterInWordToGuess[std::toupper(playerGuess[i])])--;
            }
            else
            {
                letterColor[i] = Grey;
                hasGuessedCorrectWord = false;
                nonGreenIndex.push_back(i);
            }
        }
        
        for (auto index : nonGreenIndex)
        {
            if ((word.find(std::toupper(playerGuess[index])) != std::string::npos) || (word.find(std::tolower(playerGuess[index])) != std::string::npos))
            {
                int amountOfCurrentLetterInGuess = std::get<Count>(letterCounterInPlayerGuess[std::toupper(playerGuess[index])]);
                int amountOfCurrentLetterInWord = std::get<Count>(letterCounterInWordToGuess[std::toupper(playerGuess[index])]);

                //See if we have already gotten them green
                if (amountOfCurrentLetterInWord > 0)
                {
                    letterColor[index] = Yellow;
                    std::get<Count>(letterCounterInWordToGuess[std::toupper(playerGuess[index])])--;
                }
                else
                {
                    letterColor[index] = Grey; 
                }
            }            
        }

        PrintColoredLetters(playerGuess, letterColor);

        remainingTries--;
    }
    else
    {
        std::cout << "Please type a " << word.length() << " letter word.";
        hasGuessedCorrectWord = false;
    }

    if (!hasGuessedCorrectWord)
    {
        //Type out un-used letters
        std::string letterString = "[ ";
        for (auto curChar : remainingLetters)
        {
            letterString += curChar;
            letterString += ',';
        }
        letterString[letterString.length() - 1] = ' '; //Remove trailing ','

        std::cout << std::endl << "Un-used letters: " + letterString + "]";
    }

    return hasGuessedCorrectWord;
}

void CheckLetters::CreateAlphabeteVector(const std::string& alphabet, OUT std::vector<char>* vec)
{
    for (int i = 0; i < alphabet.length(); ++i)
    {
        vec->push_back(std::toupper(alphabet[i]));
    }
}

std::unordered_map<char, std::tuple<int, std::vector<int>>> CheckLetters::MakeHashMapOfLetterCount(std::string word)
{
    // feedback: does this have to be such complicated data structure?
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounter;

    std::vector<int> indexVector;
    std::tuple<int, std::vector<int>> countAndIndex;

    for (int i = 0; i < word.length(); ++i)
    {
        if (letterCounter.contains(word[i])) continue; //No need to count letters of a character we've already counted

        int count = 0;
        //Get amount of the current letter
        for (int x = 0; ((x = word.find(word[i], x)) != std::string::npos); ++x)
        {
            count++;
            indexVector.push_back(x);
        }
        countAndIndex = std::make_tuple(count, indexVector);

        //Populate hash table
        letterCounter[std::toupper(word[i])] = countAndIndex;
    }

    return letterCounter;
}

void CheckLetters::PrintColoredLetters(std::string playerGuess, std::unordered_map<int, LetterColor> letterColor)
{
    //Print all
    for (int i = 0; i < playerGuess.length(); ++i)
    {
        BackgroundColor bg = BackgroundColor::Red;

        switch (letterColor[i])
        {
        case Green:
            bg = BackgroundColor::Green;
            break;
        case Yellow:
            bg = BackgroundColor::Yellow;
            break;
        case Grey:
            bg = BackgroundColor::None;
            break;
        case Debug:
            bg = BackgroundColor::BrightRed;
            break;
        }

        std::string txt = "";
        txt = playerGuess[i];

        if (bg == BackgroundColor::None)
        {
            std::cout << txt;
        }
        else
        {
            std::cout << BACKGROUND(bg, txt);
        }
    }
}
