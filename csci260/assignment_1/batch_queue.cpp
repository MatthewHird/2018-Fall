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
#include <algorithm>
#include <regex>


BatchQueue::BatchQueue(int queueCapacity, std::string batchFilePath)
    : queueCapacity(queueCapacity)
    , batchFilePath(std::move(batchFilePath))
{
    priorityQueue = new PriorityQueue<float,Job>(queueCapacity);
}


BatchQueue::~BatchQueue() {
    delete priorityQueue;
}


void BatchQueue::run() {
    loadBatchFile(batchFilePath);
    menu();
}


void BatchQueue::menu() {
    // menu options are:
    // submit
    // execute
    // random
    // quit
    // invalid entry

    displayMenuOptions();
    bool terminate = false;
    while (!terminate) {
        bool redisplayMenu = true;

        std::string command = getWordInput();
        std::transform(command.begin(), command.end(), command.begin(), tolower);

        if (command == "submit") {
            submitJob();
        } else if (command == "execute") {
            executeNext();
        } else if (command == "random") {
            executeRandom();
        } else if (command == "quit") {
            quitProgram();
            terminate = true;
            redisplayMenu = false;
        } else {
            std::cout << "Invalid command: please try again\n" << CMD_PROMPT;
            redisplayMenu = false;
        }

        if (redisplayMenu) {
            displayMenuOptions();
        }
    }



}


void BatchQueue::displayMenuOptions() {
    std::cout << "List menu options\n" << CMD_PROMPT;
}


void BatchQueue::loadBatchFile(std::string &batchFilePath) {}


void BatchQueue::saveBatchFile(std::string &batchFilePath) {}


void BatchQueue::submitJob() {
    if (priorityQueue->isFull()) {
        std::cout << "Cannot submit job: BatchQueue is full\n";
        return;
    }

    float estExecTime = 1.0e30;
    std::string submitterId;
    std::string startCommand;
    std::string resourceList;

    std::cout << "Input estExecTime\n" << CMD_PROMPT;

    bool invalidInput = true;
    while (invalidInput) {
        estExecTime = getFloatInput();
        if (estExecTime > 0) {
            invalidInput = false;
        } else {
            std::cout << "invalid input: try again\n" << CMD_PROMPT;
        }
    }

    std::cout << "Input submitterId\n" << CMD_PROMPT;

    invalidInput = true;
    while(invalidInput) {
        submitterId = getWordInput();
        if (submitterId.length() <= 8) {
            invalidInput = false;
        } else {
            std::cout << "invalid input: try again\n" << CMD_PROMPT;
        }
    }

    std::cout << "Input startCommand\n" << CMD_PROMPT;

    invalidInput = true;
    while(invalidInput) {
        startCommand = getWordInput();
        invalidInput = false;
    }

    std::cout << "Input resourceList\n" << CMD_PROMPT;

    invalidInput = true;
    while(invalidInput) {
        resourceList = getLineInput();
        if (resourceList.length() <= 80) {
            invalidInput = false;
        } else {
            std::cout << "invalid input: try again\n" << CMD_PROMPT;
        }
    }

    Job job;
    try {
        job = Job(estExecTime, submitterId, startCommand, resourceList);
    } catch (std::exception &e) {
        std::cout << e.what();
        return;
    }

    try {
        priorityQueue->insert(estExecTime, &job);
    } catch (FullHeapException &e) {
        std::cout << e.what();
        return;
    }

}


void BatchQueue::executeNext() {}


void BatchQueue::executeRandom() {}


void BatchQueue::quitProgram() {
    saveBatchFile(batchFilePath);
    std::cout << "Exit message\n";
}


float BatchQueue::getFloatInput() {
    float num;
    std::cin >> num;
    std::cin.ignore();
    return num;
}


std::string BatchQueue::getWordInput() {
    std::string word;
    std::getline(std::cin, word);
    return word;
}


std::string BatchQueue::getLineInput() {
    std::string line;
    std::getline(std::cin, line);
    return line;
}