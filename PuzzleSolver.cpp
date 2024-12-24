#include "PuzzleSolver.h"
#include <iostream>
#include <execution>
#include <algorithm>
#include <queue>
#include <mutex>

PuzzleSolver::PuzzleSolver(const std::vector<std::string>& numbers,
                           const std::unordered_map<int, std::vector<int>>& graph,
                           const std::vector<int>& inDegree)
    : numbers(numbers), graph(graph), inDegree(inDegree) {}

std::vector<int> PuzzleSolver::parallelTopologicalSort(int numThreads) {
    int n = numbers.size();
    std::vector<int> topoOrder;
    topoOrder.reserve(n);

    std::vector<int> localInDegree = inDegree;
    std::queue<int> zeroInDegreeQueue;
    std::mutex queueMutex;

    for (int i = 0; i < n; ++i) {
        if (localInDegree[i] == 0) zeroInDegreeQueue.push(i);
    }

    auto processNode = [&](int node) {
        topoOrder.push_back(node);
        if (graph.find(node) == graph.end()) {
            std::cerr << "Warning: Node " << numbers[node] << " is disconnected.\n";
            return;
        }
        for (int neighbor : graph.at(node)) {
            if (--localInDegree[neighbor] == 0) {
                std::lock_guard<std::mutex> lock(queueMutex);
                zeroInDegreeQueue.push(neighbor);
            }
        }
    };

    /*auto processNode = [&](int node) {
        topoOrder.push_back(node);
        try {
            for (int neighbor : graph.at(node)) { // Try accessing the node
                if (--localInDegree[neighbor] == 0) {
                    std::lock_guard<std::mutex> lock(queueMutex);
                    zeroInDegreeQueue.push(neighbor);
                }
            }
        } catch (const std::out_of_range& e) {
            std::cerr << "Error: Node " << node << " not found in graph.\n";
        }
    };*/

    while (!zeroInDegreeQueue.empty()) {
        int current;
        {
            std::lock_guard<std::mutex> lock(queueMutex);
            current = zeroInDegreeQueue.front();
            zeroInDegreeQueue.pop();
        }
        processNode(current);
    }

    return topoOrder;
}


std::string PuzzleSolver::computeLongestPath(const std::vector<int>& topoOrder, int numThreads) {
    std::vector<std::string> dp(numbers.size());

    std::for_each(std::execution::par, topoOrder.begin(), topoOrder.end(), [&](int node) {
        if (dp[node].empty()) dp[node] = numbers[node];
        for (int neighbor : graph.at(node)) {
            std::string newChain = dp[node] + numbers[neighbor].substr(2);
            if (newChain.size() > dp[neighbor].size() ||
                (newChain.size() == dp[neighbor].size() && newChain > dp[neighbor])) {
                dp[neighbor] = newChain;
            }
        }
    });

    return *std::max_element(dp.begin(), dp.end(), [](const std::string& a, const std::string& b) {
        return a.size() < b.size() || (a.size() == b.size() && a < b);
    });
}

std::string PuzzleSolver::solve(int numThreads) {
    auto topoOrder = parallelTopologicalSort(numThreads);
    return computeLongestPath(topoOrder, numThreads);
}
