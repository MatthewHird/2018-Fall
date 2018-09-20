//------------------------------------------------------------------------------
// @file       batch_queue.cpp
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#include "batch_queue.h"
#include "priority_queue.h"
#include "job.h"
#include <iostream>


BatchQueue::BatchQueue() {}


BatchQueue::~BatchQueue() {}


void BatchQueue::run(std::string batchFilePath) {
    std::cout << batchFilePath << "\n";
}


void menu() {
    // menu options are:
    // submit
    // execute
    // random
    // quit
    // invalid entry
}


void BatchQueue::loadBatchFile(std::string batchFilePath) {}


void BatchQueue::saveBatchFile(std::string batchFilePath) {}


void BatchQueue::submitJob() {}


void BatchQueue::executeNext() {}


void BatchQueue::executeRandom() {}


void BatchQueue::quitProgram() {}
