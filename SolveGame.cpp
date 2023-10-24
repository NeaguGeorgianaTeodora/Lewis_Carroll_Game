#include "SolveGame.h"
#include<unordered_set>
#include<queue>

void createGraph(Graph<std::string>& graph, int nrLetters)
{
    std::unordered_map<std::string, std::vector<std::string>> patternMap;
    createDictionary("Words.txt", patternMap);


    //add vertices to the graph
    for (auto& pair : patternMap)
    {
        if (pair.first.size() == nrLetters)
        {
            for (auto& word : pair.second)
            {
                graph.addVertex(word);
            }

            //add edges between words that differ by one letter
            for (int i = 0; i < pair.second.size() - 1; i++)
            {
                for (int j = i + 1; j < pair.second.size(); j++)
                {
                    if (pair.second[i] != pair.second[j])
                    {
                        graph.addEdge(pair.second[i], pair.second[j]);
                    }
                }
            }
        }
    }
}


std::vector<std::string> shortestPath(Graph<std::string>& graph, std::string start, std::string target)
{
    // Create a visited set to keep track of visited nodes
    std::unordered_set<std::string> visited;

    // Create a queue for BFS
    std::queue<std::pair<std::string, std::vector<std::string>>> q;

    // Mark the starting node as visited and enqueue it with an empty path
    visited.insert(start);
    q.push({ start, {start} });

    // Loop until the queue is empty
    while (!q.empty()) {
        // Dequeue a vertex from queue and get its path
        std::string curr = q.front().first;
        std::vector<std::string> path = q.front().second;
        q.pop();

        // If the dequeued vertex is the target, return its path
        if (curr == target)
        {
            return path;
        }

        // Get all adjacent vertices of the dequeued vertex curr
        std::vector<std::string> neighbors = graph.getGraph()[curr];

        // Traverse through all adjacent vertices
        for (auto neighbor : neighbors)
        {
            // If a neighbor is not visited, mark it visited and enqueue it with the current path plus the neighbor
            if (visited.find(neighbor) == visited.end())
            {
                visited.insert(neighbor);
                std::vector<std::string> newPath = path;
                newPath.push_back(neighbor);
                q.push({ neighbor, newPath });
            }
        }
    }

    // If the target is not reachable from the starting node, return an empty path
    return {};
}