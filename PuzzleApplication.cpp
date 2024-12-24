#include "PuzzleApplication.h"
#include "FileReader.h"
#include "GraphBuilder.h"
#include "PuzzleSolver.h"
#include <iostream>
#include <thread>
void PuzzleApplication::run(int argc, char* argv[]) {
    try {
        std::string filename = (argc > 1) ? argv[1] : "source0.txt";
        int numThreads = (argc > 2) ? std::stoi(argv[2]) : std::thread::hardware_concurrency();

        std::cout << "Using " << numThreads << " threads." << std::endl;

        std::vector<std::string> numbers = FileReader::getInstance()->readFile(filename);
        if (numbers.empty()) {
            std::cerr << "Error: No valid numbers found in the file." << std::endl;
            return;
        }

        GraphBuilder graphBuilder;
        graphBuilder.buildGraph(numbers, numThreads);

        PuzzleSolver solver(numbers, graphBuilder.getGraph(), graphBuilder.getInDegree());
        std::string result = solver.solve(numThreads);

        std::cout << "Largest sequence: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
}
