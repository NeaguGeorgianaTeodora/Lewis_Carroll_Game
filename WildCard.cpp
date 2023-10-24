#include"WildCard.h"
#include<fstream>
#include<iostream>
#include<algorithm>

std::string replaceLetter(std::string pattern, int index)
{
    std::string word = pattern;
    word[index] = '*';
    return word;
}

void createDictionary(std::string path, std::unordered_map<std::string, std::vector<std::string>>& patternMap)
{

    std::ifstream fin(path);

    if (!fin.is_open())
    {
        std::cout << "Error opening file" << std::endl;
        return;
    }

    std::string word;

    while (getline(fin, word))
    {
        for (int i = 0; i < word.length(); i++)
        {
            std::string pattern = replaceLetter(word, i);
            if (patternMap.find(pattern) != patternMap.end())
            {
                if (std::binary_search(patternMap[pattern].begin(), patternMap[pattern].end(), word) == 0)
                    patternMap[pattern].push_back(word);
            }
            else
            {
                patternMap.insert(std::pair<std::string, std::vector<std::string>>(pattern, std::vector<std::string>()));
                patternMap[pattern].push_back(word);
            }
        }
    }

    fin.close();
}