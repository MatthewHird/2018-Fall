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