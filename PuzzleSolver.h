#ifndef PUZZLESOLVER_H
#define PUZZLESOLVER_H

#include <vector>
#include <string>
#include <unordered_map>

class PuzzleSolver {
public:
    PuzzleSolver(const std::vector<std::string>& numbers,
                 const std::unordered_map<int, std::vector<int>>& graph,
                 const std::vector<int>& inDegree);

    std::string solve(int numThreads = 4); // Solves the puzzle with parallel execution

private:
    std::vector<std::string> numbers;
    std::unordered_map<int, std::vector<int>> graph;
    std::vector<int> inDegree;

    std::vector<int> parallelTopologicalSort(int numThreads); // Parallelized topological sort
    std::string computeLongestPath(const std::vector<int>& topoOrder, int numThreads); // Parallel DP
};

#endif // PUZZLESOLVER_H
