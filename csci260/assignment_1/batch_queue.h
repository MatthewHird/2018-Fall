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

    void run();

private:

    void menu();
    void displayMenuOptions();
    void loadBatchFile(std::string &batchFilePath);
    void saveBatchFile(std::string &batchFilePath);

    void submitJob();
    void executeNext();
    void executeRandom();
    void quitProgram();

    int insertJob(float estExecTime, std::string submitterId,
            std::string startCommand, std::string resourceList);

    float getFloatInput();
    std::string getWordInput(int maxLength=0);
    std::string getLineInput(int maxLength=0);

    const std::string CMD_PROMPT = ">>>  ";
    int queueCapacity;
    std::string batchFilePath;
    std::string testOutputFile = "batch_TEST.txt";
    PriorityQueue<float,Job>* priorityQueue;
};

#endif //ASSIGNMENT_1_BATCH_QUEUE_H
