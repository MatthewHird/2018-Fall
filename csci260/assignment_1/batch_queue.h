//------------------------------------------------------------------------------
// @file       batch_queue.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_BATCH_QUEUE_H
#define ASSIGNMENT_1_BATCH_QUEUE_H

#include <iostream>
#include "job.h"
#include "priority_queue.h"
#include "my_exceptions.h"


class BatchQueue {
public:
    explicit BatchQueue(int queueCapacity=10, std::string batchFilePath="batch.txt");
    ~BatchQueue();

    void run(int queueCapacity=10, std::string batchFilePath="batch.txt");

private:

    void menu();
    void loadBatchFile(std::string &batchFilePath);
    void saveBatchFile(std::string &batchFilePath);

    void submitJob();
    void executeNext();
    void executeRandom();
    void quitProgram();

    float getFloatInput();
    std::string getWordInput();
    std::string getLineInput();

    int queueCapacity;
    std::string batchFilePath;
    PriorityQueue<float,Job>* priorityQueue;
};

#endif //ASSIGNMENT_1_BATCH_QUEUE_H
