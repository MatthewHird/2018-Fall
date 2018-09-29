#include <utility>

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


BatchQueue::BatchQueue(int queueCapacity, std::string batchFilePath)
    : queueCapacity(queueCapacity)
    , batchFilePath(std::move(batchFilePath))
{
    priorityQueue = new PriorityQueue<double,Job>(queueCapacity);
}


BatchQueue::~BatchQueue() {
    delete priorityQueue;
}


void BatchQueue::run(int queueCapacity, std::string batchFilePath) {
    std::cout << queueCapacity << " " << batchFilePath << "\n";
}


void BatchQueue::menu() {
    // menu options are:
    // submit
    // execute
    // random
    // quit
    // invalid entry
}


void BatchQueue::loadBatchFile(std::string& batchFilePath) {}


void BatchQueue::saveBatchFile(std::string& batchFilePath) {}


void BatchQueue::submitJob() {}


void BatchQueue::executeNext() {}


void BatchQueue::executeRandom() {}


void BatchQueue::quitProgram() {}


float BatchQueue::getFloatInput() {}


std::string BatchQueue::getWordInput() {}


std::string BatchQueue::getLineInput() {}