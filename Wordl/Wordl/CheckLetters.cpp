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

enum LetterColor
{
    Green,
    Yellow,
    Grey,
    Debug
};


/*bool CheckLetters::CheckWord(std::string word, std::string playerGuess, int& remainingTries, std::vector<char>& remainingLetters)
{
    bool hasGuessedCorrectWord = true;
    //Letter, tuple <count, indices>
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounterInWordToGuess;
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounterInPlayerGuess;

    bool showYellowLetters = true;
    int yellowsToShow = 0;
    
    if (playerGuess.length() == word.length())
    {
        //Calculat/check instances of letters
        letterCounterInWordToGuess = MakeHashMapOfLetterCount(word);
        letterCounterInPlayerGuess = MakeHashMapOfLetterCount(playerGuess);

        //Check letters
        for (int i = 0; i < word.length(); i++)
        {           
            auto amountOfLetterInWord = letterCounterInWordToGuess[std::toupper(playerGuess[i])];
            auto amountOfLetterInPlayerGuess = letterCounterInPlayerGuess[std::toupper(playerGuess[i])];

            if (std::get<Indices>(amountOfLetterInWord).size() <= std::get<Indices>(amountOfLetterInPlayerGuess).size() && std::get<Indices>(amountOfLetterInPlayerGuess).size() != 0 &&  std::get<Indices>(amountOfLetterInWord).size() != 0)
            {
                std::vector<int> wordIndices = std::get<Indices>(amountOfLetterInWord);
                std::vector<int> guessIndices = std::get<Indices>(amountOfLetterInPlayerGuess);

                int inCorrectSpot = 0;
                for (int x = i; x < wordIndices.size(); x++)
                {
                    if (wordIndices[x] == guessIndices[x])
                    {
                        inCorrectSpot++;     
                    }
                }

                if (inCorrectSpot == 0 && inCorrectSpot >= wordIndices.size() && letterCounterInWordToGuess.contains(playerGuess[i]))
                {
                    showYellowLetters = false;
                }                
            }
            
            //Remove current letter from available letters
            remainingLetters.erase(std::remove(remainingLetters.begin(), remainingLetters.end(), std::toupper(playerGuess[i])), remainingLetters.end());

            bool caseInsensitiveCompare = std::to_string(std::tolower(playerGuess[i])) == std::to_string(std::tolower(word[i]));

            //If the 'player' has written a word with multiples of one letter, we check if the word has more than one of that letter, otherwise we print the n-th instance of the letter as grey.
            bool letterIsValid = false;            
            if (caseInsensitiveCompare && std::get<Count>(letterCounterInWordToGuess[std::toupper(playerGuess[i])]) > 0)
            {
                letterIsValid = true;                
                std::get<Count>(letterCounterInWordToGuess[playerGuess[i]])--;
            }            
            
            if (caseInsensitiveCompare /*&& letterIsValid#1#)
            {
                std::cout << BACKGROUND(BackgroundColor::Green,playerGuess[i]);
            }                
            else if (showYellowLetters && (word.find(std::toupper(playerGuess[i])) != std::string::npos) || (word.find(std::tolower(playerGuess[i]))!= std::string::npos ))
            {
                std::cout << BACKGROUND(BackgroundColor::BrightYellow,playerGuess[i]);
                hasGuessedCorrectWord = false;
            }
            else
            {
                std::cout << playerGuess[i];
                hasGuessedCorrectWord = false;
            }            
        }        
        remainingTries--;
    }
    else
    {            
        std::cout << "Please type a " << word.length() << " letter word." ;
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
        letterString[letterString.length()-1] = ' '; //Remove trailing ','

        std::cout << std::endl<< "Un-used letters: " + letterString + "]";
    }    

    return hasGuessedCorrectWord;
}*/




bool CheckLetters::CheckWord(std::string word, std::string playerGuess, int& remainingTries,std::vector<char>& remainingLetters)
{
    bool hasGuessedCorrectWord = true;

    //Letter, tuple <count, indices>
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounterInWordToGuess;
    std::unordered_map<char, std::tuple<int, std::vector<int>>> letterCounterInPlayerGuess;

    //index + green/yellow/nothing
    std::unordered_map<int, int> letterColor;
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

        //Print greens debug
        /*for (int i = 0; i < playerGuess.length(); ++i)
        {
            BackgroundColor bg = BackgroundColor::Red;

            switch (letterColor[i])
            {
            case 0:
                bg = BackgroundColor::Green;
                break;
            case 1:
                bg = BackgroundColor::Yellow;
                break;
            case 2:
                bg = BackgroundColor::None;
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
        }*/

        for (auto index : nonGreenIndex)
        {
            //std::cout << std::endl << playerGuess[index] << "   <- Was wrong" << std::endl; // debug

            if ((word.find(std::toupper(playerGuess[index])) != std::string::npos) || (word.find(std::tolower(playerGuess[index])) != std::string::npos))
            {
                int amountOfCurrentLetterInGuess = std::get<Count>(letterCounterInPlayerGuess[std::toupper(playerGuess[index])]);
                int amountOfCurrentLetterInWord = std::get<Count>(letterCounterInWordToGuess[std::toupper(playerGuess[index])]);

                //std::cout << "Amount in guess: " << amountOfCurrentLetterInGuess << "  Amount in word: " << amountOfCurrentLetterInWord << std::endl; //debug
                
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

        //std::cout << "Amt of " << word[i] << "  " << std::get<0>(countAndIndex) << std::endl; //debug

        //Populate hash table
        letterCounter[std::toupper(word[i])] = countAndIndex;
    }

    return letterCounter;
}

void CheckLetters::PrintColoredLetters(std::string playerGuess, std::unordered_map<int, int> letterColor)
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
