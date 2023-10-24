#include "Menu.h"
#define M "\033[1;35m"
#include <chrono>
#include <ctime>
#include <fstream>
#include <sstream>
#include <unordered_set>

void runAutomathicMode()
{
    std::cout << "Enter the starting word: ";
    std::string start;
    std::cin >> start;
    std::cout << std::endl;

    std::cout << "Enter the target word: ";
    std::string target;
    std::cin >> target;
    std::cout << std::endl;

    if (start.size() != target.size())
    {
        std::cout << "The words must have the same size." << std::endl;
    }
    else
    {
        Graph<std::string> graph;
        createGraph(graph, start.size());

        std::vector<std::string> path = shortestPath(graph, start, target);

        if (path.size() == 0)
        {
            std::cout << "No solution found." << std::endl;
        }
        else
        {
            std::cout << "Solution: ";
            for (auto& word : path)
            {
                std::cout << word << " ";
            }
            std::cout << std::endl;
        }
    }
}

std::string generateRandomPair(Graph<std::string>& graph, int nrLetters, std::string& start, std::string& target)
{
    createGraph(graph, nrLetters);

    int nr1;
    nr1 = rand() % graph.getGraph().size();

    int nr2;
    nr2 = rand() % graph.getGraph().size();

    for (auto& pair : graph.getGraph())
    {
        nr1--;
        nr2--;
        if (nr1 == 0)
        {
            start = pair.first;
            nr1 = -1;
        }

        if (nr2 == 0)
        {
            target = pair.first;
            nr2 = -1;
        }
        if (nr1 <= 0 && nr2 <= 0)
            break;
    }
    return start;
}

void validateNumber(int nr)
{
    while (nr > 20 || nr < 1)
    {
        std::cout << "Not a valid number. Please try again." << std::endl;
        std::cin >> nr;
        std::cout << std::endl;
    }
}

void gameTime(char time_buffer[26])
{

    const auto now = std::chrono::system_clock::now();
    const std::time_t t_c = std::chrono::system_clock::to_time_t(now);

    ctime_s(time_buffer, 26, &t_c);


}

bool findWord(Graph<std::string> graph, std::string word, std::string toFind)
{
    for (auto& pair : graph.getGraph())
    {
        if (pair.first == word)
        {
            for (auto& wrd : pair.second)
            {
                if(wrd == toFind)
                    return true;
            }
        }
    }
    return false;
}

void getHint(std::vector<std::string> path, Graph<std::string> graph, std::string start, std::string target)
{
    std::string hint;

    for (int i = 0; i < path.size(); i++)
    {
        if (path[i] == start)
        {
            hint = path[i + 1];
            break;
        }
    }

    for (int i = 0; i < hint.size(); i++)
    {
        if (hint[i] != start[i])
        {

            std::cout << "\033[1;35m" << start[i] << "\033[0m";
        }
        else
        {
            std::cout << start[i];
        }
    }

    std::cout << std::endl;
}

void saveData(std::string name, int nrOfHints, int nrOfMoves, int minNrMoves,std::string start, std::string target, std::vector<std::string> userSolution)
{
    std::string filename = "username.csv";
    std::ofstream file;

    // Open file for append
    file.open(filename, std::ios_base::app);

    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    // Write data to file
    std::string username = name;
    char time_buffer[26];
    gameTime(time_buffer);

    file <<"The system clock is currently at " << time_buffer << std::endl;
    file << "username: " << username << std::endl;
    file<< "number of hints: "<< nrOfHints << std::endl;
    file<< "number of moves: "<< nrOfMoves << std::endl;
    file<< "minimum number of moves: "<< minNrMoves << std::endl;
    file<< "start word: "<< start << std::endl;
    file<< "target word: "<< target << std::endl;
    file<< "user solution: ";

    for (auto& word : userSolution)
    {
        file << word << " ";
    }
    file << std::endl;
    file << std::endl;
    file << std::endl;

    // Close file
    file.close();

}

void runPlayMode(bool& ok)
{
    std::cout << "YOU ENTERED PLAY MODE" << std::endl;
    std::cout << "You can ask for hints by pressing 'h'" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter your name: ";
    std::string name;
    std::cin >> name;
    std::cout << std::endl;

    std::cout << "Enter how many letters should the words have: ";
    int nr;
    std::cin >> nr;
    std::cout << std::endl;

    validateNumber(nr);

    std::string start;
    std::string target;
    Graph<std::string> graph;
    generateRandomPair(graph, nr, start, target);
    std::vector<std::string> path = shortestPath(graph, start, target);
    int minNrMoves = path.size() - 1;

    std::cout << "The starting word is: " << start << std::endl;
    std::cout << "The target word is: " << target << std::endl;

    std::string userInput;
    std::cout << "Enter the next word: ";
    std::cin >> userInput;
    std::cout << std::endl;
    std::string currrentWord = start;
    std::vector<std::string> userSolution;
    userSolution.push_back(currrentWord);
    int nrOfHints = 0;
    int nrOfMoves = 1;
    ok = false;


    while (userInput != target)
    {
        if (userInput == "h" || userInput == "H")
        {
            getHint(path,graph, currrentWord, target);
            nrOfHints++;
            ok = true;
        }
        else
        {
            if (findWord(graph, currrentWord, userInput) == true)
            {
                currrentWord = userInput;
                userSolution.push_back(currrentWord);
                ok = true;
            }
            else
            {
                ok = false;
                break;
            }

        }
        nrOfMoves++;
        std::cout << "Enter the next word: ";
        std::cin >> userInput;
        std::cout << std::endl;
    }
    userSolution.push_back(target);

    saveData(name, nrOfHints, nrOfMoves, minNrMoves,start, target, userSolution);

    if (ok)
    {
        std::cout << "Congratulations " << name << "!" << std::endl;
        std::cout << "You won the game!" << std::endl;
    }
    else
    {

        std::cout << "Incorect word." << std::endl;
        std::cout << "END GAME" << std::endl;
    }
}



void runAnalythicsMode()
{
    std::cout << "YOU ENTERED ANALYTHICS MODE" << std::endl;
    std::cout << std::endl;

    std::cout << "Enter the name of the user you want to know data about: ";
    std::string name;
    std::cin >> name;
    std::cout << std::endl;

    std::string filename = "username.csv";
    std::ifstream file;

    // Open file for append
    file.open(filename, std::ios_base::app);
    if (!file)
    {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    bool ok = false;
    std::string line;
    std::string data;
    std::unordered_set<std::string> userSolution;
    std::string currentName;
    int nrOfHints;
    int nrOfMoves;
    int minNrMoves;
    int nrUniqueWords;

    while (std::getline(file, line))
    {
        std::istringstream lineStream(line);
        std::string key, value;

        if (std::getline(lineStream, key, ':') && std::getline(lineStream, value))
        {
            if (key == "username")
            {
                // Remove leading and trailing double quotes from the value
                value = value.substr(1, value.size() - 1);
                currentName.assign(value);
            }

            if (currentName == name)
            {
                ok = true;
                std::string line1;
                while (std::getline(file, line1))
                {

                    std::istringstream lineStream1(line1);
                    std::string key1, value1;

                    if (std::getline(lineStream1, key1, ':') && std::getline(lineStream1, value1))
                    {
                        if (key1 == "number of hints")
                        {
                            nrOfHints = std::stoi(value1);
                        }
                        if (key1 == "number of moves")
                        {
                            nrOfMoves = std::stoi(value1);
                        }
                        if (key1 == "minimum number of moves")
                        {
                            minNrMoves = std::stoi(value1);
                        }
                        if (key1 == "user solution")
                        {
                            value1 = value1.substr(1,value1.size()-1);

                            std::istringstream iss(value1);
                            std::string word;
                            while (std::getline(iss, word, ' '))
                            {
                                userSolution.insert(word);
                            }
                        }
                    }
                }
                break;
            }
        }
    }

    if (!ok)
    {
        std::cout << "There is no user with this name." << std::endl;
        return;
    }

    std::cout<<"The user " << name << " has used "<< "\033[1;32m" << userSolution.size() << "\033[0m"<< "\033[1;34m" << " unique words"<< "\033[0m" << std::endl;
    std::cout << "The user " << name << " has used " << "\033[1;32m" << nrOfHints << "\033[0m" << "\033[1;34m" << " hints" << "\033[0m" << std::endl;
    std::cout << "The user " << name << " has made " << "\033[1;32m" << nrOfMoves << "\033[0m" << "\033[1;34m" << " moves" << "\033[0m" << std::endl;
    std::cout << "The " << "\033[1;34m" <<"minimum number of moves " << "\033[0m" <<"was " << "\033[0m" << "\033[1; 32m" << minNrMoves << "\033[0m" << std::endl;
    std::cout << std::endl;
}

void menu()
{
    std::cout << "Presse 1 to start the automathic mode." << std::endl;
    std::cout << "Presse 2 to start the play mode." << std::endl;
    std::cout << "Presse 3 to start the analythics mode." << std::endl;
    std::cout << "Presse 0 to exit game." << std::endl;

    bool ok = true;

    while (ok)
    {
        std::cout << "Enter a choice: ";

        int choice;

        std::cin >> choice;

        if(choice == 0 || choice == 1 || choice == 2 || choice == 3)
        {

            switch (choice)
            {
                case 0:
                {
                    std::cout << "END GAME" << std::endl;
                    ok = false;
                    break;
                }
                case 1:
                {
                    runAutomathicMode();
                    break;
                }
                case 2:
                {
                    bool ok1 = true;
                    runPlayMode(ok1);
                    ok = false;
                    break;
                }
                case 3:
                {
                    runAnalythicsMode();
                    break;
                }
                default:
                    break;
            }
        }
        else
        {
            std::cout << "Not a valid choice. Please try again." << std::endl;
            std::cin >> choice;
        }
    }
}