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
#include <fstream>


BatchQueue::BatchQueue(int queueCapacity, std::string batchFilePath)
    : queueCapacity(queueCapacity)
    , batchFilePath(batchFilePath)
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


void BatchQueue::loadBatchFile(std::string &batchFilePath) {
    std::ifstream inputFile;
    inputFile.open(batchFilePath.c_str());
    try {
        if (inputFile.fail()) {
            std::cout << "Failed to load inputFile: unable to open " << batchFilePath << "\n";
        } else {
            int entryCount;
            inputFile >> entryCount;
            inputFile.ignore();

            for (int i = 0; i < entryCount; i++) {
                float estExecTime = 0;
                std::string submitterId;
                std::string startCommand;
                std::string resourceList;

                inputFile >> estExecTime;
                inputFile.ignore();
                std::getline(inputFile, submitterId);
                std::getline(inputFile, startCommand);
                std::getline(inputFile, resourceList);

                Job* job;
                try {
                    job = new Job(estExecTime, submitterId, startCommand, resourceList);

                } catch (std::exception &e) {
                    std::cout << e.what();
                    std::cout << "Failed to load inputFile: inputFile contains invalid data\n";
                    break;
                }

                try {
                    priorityQueue->insert(estExecTime, job);
                } catch (FullHeapException &e) {
                    std::cout << "Failed to load entry " << (i + 1) << " from inputFile: batch queue is full\n";
                }

            }
            inputFile.close();
        }
    } catch (std::exception &e) {
        std::cout << "Failed to load inputFile: invalid syntax in " << batchFilePath << "\n";
    }
}


void BatchQueue::saveBatchFile(std::string &batchFilePath) {
    int entryCount = priorityQueue->getSize();
    std::stringstream stringStream;
    stringStream << entryCount << "\n";

    for (int i = 0; i < entryCount; i++) {
        Job* job = priorityQueue->removeMin();

        stringStream << job->getEstExecTime() << "\n";
        stringStream << job->getSubmitterId() << "\n";
        stringStream << job->getStartCommand() << "\n";
        stringStream << job->getResourceList() << "\n";
    }

    std::string saveString = stringStream.str();

    std::ofstream outFile;
    outFile.open(batchFilePath.c_str());
    if (outFile.fail()) {
        std::cout << "Failed to open " << batchFilePath << ": attempting to save to backup file batch_queue_backup.txt instead\n";
        outFile.open("batch_queue_backup.txt");
        if (outFile.fail()) {
            std::cout << "Failed to open batch_queue_backup.txt: aborting program without saving\n";

        } else {
            outFile << saveString;
        }
    } else {
        outFile << saveString;
    }
}


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

    Job* job;
    try {
        job = new Job(estExecTime, submitterId, startCommand, resourceList);
    } catch (std::exception &e) {
        std::cout << e.what();
        return;
    }

    try {
        priorityQueue->insert(estExecTime, job);
    } catch (FullHeapException &e) {
        std::cout << e.what();
        return;
    }

}


void BatchQueue::executeNext() {
    Job* job = priorityQueue->removeMin();
    std::cout << job->getEstExecTime() << " " << job->getSubmitterId() << " "
        << job->getStartCommand() << " " << job->getResourceList() << "\n";
    delete job;
}


void BatchQueue::executeRandom() {}


void BatchQueue::quitProgram() {
//    saveBatchFile(batchFilePath);
    saveBatchFile(testOutputFile);
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