//------------------------------------------------------------------------------
// @file    main.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   The main function for the program pex1. Checks commandline
//          arguments, then starts BatchQueue controller class.
//------------------------------------------------------------------------------

#include <iostream>
#include "batch_queue.h"


/**
 * .pex1 [queueCapacity]
 *
 * queueCapacity    the maximum number of jobs the batch queue can contain (default = 10).
 */
int main(int argc, char **argv) {
    if (argc > 2) {
        std::cout << "Error: Invalid number of arguments\n";
        return 1;
    }

    int queueCapacity = 10;

    if (argc == 2) {

        try {
            queueCapacity = std::stoi(argv[1]);
        } catch(std::invalid_argument &e) {
            queueCapacity = 0;
        }

        if (queueCapacity <= 0) {
            std::cout << "Error: Argument[1] (Queue Capacity) must be a positive integer\n";
            return 1;
        }
    }

    BatchQueue batchQueue(queueCapacity);
    batchQueue.run();
    return 0;
}