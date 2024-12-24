cmake_minimum_required(VERSION 3.16)

project(parallel_puzzle LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(parallel_puzzle main.cpp
    GraphBuilder.h
    PuzzleSolver.h PuzzleSolver.cpp
    GraphBuilder.cpp
    PuzzleApplication.cpp
    PuzzleApplication.h
    FileReader.h FileReader.cpp)

include(GNUInstallDirs)
install(TARGETS parallel_puzzle
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
