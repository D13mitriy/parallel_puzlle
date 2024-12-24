#include "PuzzleApplication.h"
#include <chrono>
#include <iostream>

int main(int argc, char* argv[]) {
    try {
        auto start = std::chrono::high_resolution_clock::now();

        PuzzleApplication app;
        app.run(argc, argv);

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
        std::cout << "Execution Time: " << duration << " ms" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
