//------------------------------------------------------------------------------
// @file    main.cpp
// @author  Matthew Hird
// @date    November November 28, 2018
//
// @brief   The main function for the program pex3. Checks commandline
//          arguments, then starts socialInfluenceAnalyzer controller class.
//------------------------------------------------------------------------------

#include <iostream>
#include <fstream>

#include "social_influence_analyzer.h"


int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "Error: Not enough arguments\n";
        return 1;
    }
    if (argc > 2) {
        std::cout << "Error: Too many enough arguments\n";
        return 2;
    }
    std::string argument = argv[1];
    if (argument == "-h" || argument == "--help") {
        std::cout << "Display Help Message Here\n";
        return 0;
    }


    std::ifstream file(argument.c_str());
    if (!file.good()) {
        std::cout << "Error: " << argument << " is not a file\n";
        return 3;
    }

    SocialInfluenceAnalyzer socialInfluenceAnalyzer;
    socialInfluenceAnalyzer.run(argument);
    return 0;
}