#include "GetWordFromFile.h"

#include <fstream>
#include <iostream>
#include <unordered_set>

std::string GetWordFromFile::GetWordToGuess()
{
    std::ifstream inputFile("words.txt");
    std::string curLine = "";
    std::vector<std::string> strVec;
    srand(time(0)); //initialize pseudo-random
    
    int i = 0;
    while (std::getline(inputFile, curLine))
    {
        strVec.push_back(curLine);
    }

    const auto word = strVec[rand() % strVec.size()];
    
    std::string wordFromFile = word;    

    return wordFromFile; // feedback: those 3 lines could be one: return strVec[rand() % strVec.size()];
}
