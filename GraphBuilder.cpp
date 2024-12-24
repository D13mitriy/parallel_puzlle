#include "GraphBuilder.h"
#include <iostream>
#include <thread>

namespace Utils {
std::string getFirstTwoDigits(const std::string& num) { return num.substr(0, 2); }
std::string getLastTwoDigits(const std::string& num) { return num.substr(num.size() - 2, 2); }
}

void GraphBuilder::addEdge(int from, int to) {
    std::lock_guard<std::mutex> lock(graphMutex);
    graph[from].push_back(to);
    ++inDegree[to];
}

void GraphBuilder::buildGraph(const std::vector<std::string>& numbers, int numThreads) {
    int n = numbers.size();
    inDegree.resize(n, 0);

    auto computeEdges = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            std::string endDigits = Utils::getLastTwoDigits(numbers[i]);
            for (int j = 0; j < n; ++j) {
                if (i != j && Utils::getFirstTwoDigits(numbers[j]) == endDigits) {
                    addEdge(i, j);
                    std::cout << "Edge added: " << numbers[i] << " -> " << numbers[j] << std::endl;
                }
            }
        }
    };

    int chunkSize = (n + numThreads - 1) / numThreads;
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(n, start + chunkSize);
        threads.emplace_back(computeEdges, start, end);
    }

    for (auto& thread : threads) thread.join();

    // Log nodes with no outgoing edges
    for (int i = 0; i < n; ++i) {
        if (graph.find(i) == graph.end() || graph[i].empty()) {
            std::cerr << "Warning: Node " << numbers[i] << " has no outgoing edges.\n";
        }
    }
}


/*
void GraphBuilder::buildGraph(const std::vector<std::string>& numbers, int numThreads) {
    int n = numbers.size();
    inDegree.resize(n, 0);

    auto computeEdges = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            std::string endDigits = Utils::getLastTwoDigits(numbers[i]);
            for (int j = 0; j < n; ++j) {
                if (i != j && Utils::getFirstTwoDigits(numbers[j]) == endDigits) {
                    addEdge(i, j);
                }
            }
        }
    };

    int chunkSize = (n + numThreads - 1) / numThreads;
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(n, start + chunkSize);
        threads.emplace_back(computeEdges, start, end);
    }

    for (auto& thread : threads) thread.join();

    // Validate graph after construction
    for (const auto& [node, neighbors] : graph) {
        if (neighbors.empty()) {
            std::cerr << "Warning: Node " << node << " has no outgoing edges.\n";
        }
    }
}

void GraphBuilder::buildGraph(const std::vector<std::string>& numbers, int numThreads) {
    int n = numbers.size();
    inDegree.resize(n, 0);

    auto computeEdges = [&](int start, int end) {
        for (int i = start; i < end; ++i) {
            std::string endDigits = Utils::getLastTwoDigits(numbers[i]);
            for (int j = 0; j < n; ++j) {
                if (i != j && Utils::getFirstTwoDigits(numbers[j]) == endDigits) {
                    addEdge(i, j);
                }
            }
        }
    };

    int chunkSize = (n + numThreads - 1) / numThreads;
    std::vector<std::thread> threads;
    for (int t = 0; t < numThreads; ++t) {
        int start = t * chunkSize;
        int end = std::min(n, start + chunkSize);
        threads.emplace_back(computeEdges, start, end);
    }

    for (auto& thread : threads) thread.join();
}*/

const std::unordered_map<int, std::vector<int>>& GraphBuilder::getGraph() const {
    return graph;
}

const std::vector<int>& GraphBuilder::getInDegree() const {
    return inDegree;
}
