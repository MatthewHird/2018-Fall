//------------------------------------------------------------------------------
// @file    batch_queue.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_BATCH_QUEUE_H
#define ASSIGNMENT_1_BATCH_QUEUE_H

#include <iostream>
#include "job.h"
#include "priority_queue.h"
#include "my_exceptions.h"


class BatchQueue {
public:
    /**
     * @brief
     * @param queueCapacity
     * @param batchFilePath
     */
    explicit BatchQueue(int queueCapacity=10, std::string batchFilePath="batch.txt");

    /**
     * @brief
     */
    ~BatchQueue();

    /**
     * @brief
     */
    void run();

private:
    /**
     * @brief
     */
    void menu();

    /**
     * @brief
     */
    void displayMenuOptions();

    /**
     * @brief
     * @param batchFilePath
     */
    void loadBatchFile(std::string &batchFilePath);

    /**
     * @brief
     * @param batchFilePath
     */
    void saveBatchFile(std::string &batchFilePath);

    /**
     * @brief
     */
    void submitJob();

    /**
     * @brief
     */
    void executeNext();

    /**
     * @brief
     */
    void executeRandom();

    /**
     * @brief
     */
    void quitProgram();

    /**
     * @brief
     * @param estExecTime
     * @param submitterId
     * @param startCommand
     * @param resourceList
     * @return
     */
    int insertJob(float estExecTime, std::string submitterId,
            std::string startCommand, std::string resourceList);

    /**
     * @brief
     * @return
     */
    float getFloatInput();

    /**
     * @brief
     * @param maxLength
     * @return
     */
    std::string getWordInput(int maxLength=0);

    /**
     * @brief
     * @param maxLength
     * @return
     */
    std::string getLineInput(int maxLength=0);

    /**
     * @brief
     * @param job
     */
    void executeJob(Job* job);

    const std::string CMD_PROMPT = ">>>  ";
    const std::string LINE_BREAK =
            "-------------------------------------------------\n\n";
    int queueCapacity;
    std::string batchFilePath;
    std::string testOutputFile = "batch_TEST.txt";
    PriorityQueue<float,Job>* priorityQueue;
};

#endif //ASSIGNMENT_1_BATCH_QUEUE_H
