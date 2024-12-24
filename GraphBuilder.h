#ifndef GRAPHBUILDER_H
#define GRAPHBUILDER_H

#include <unordered_map>
#include <vector>
#include <string>
#include <mutex>

class GraphBuilder {
public:
    void buildGraph(const std::vector<std::string>& numbers, int numThreads = 4); // Parallel graph construction
    const std::unordered_map<int, std::vector<int>>& getGraph() const;
    const std::vector<int>& getInDegree() const;

private:
    std::unordered_map<int, std::vector<int>> graph;
    std::vector<int> inDegree;
    std::mutex graphMutex; // To synchronize edge additions

    void addEdge(int from, int to); // Thread-safe edge addition
};

#endif // GRAPHBUILDER_H
