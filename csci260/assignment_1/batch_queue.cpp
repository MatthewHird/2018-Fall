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
#include <limits>


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
    std::cout << "\n**** Welcome to the Batch Queue System ****\n\n";

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
            std::cout << "Invalid command: please try again\n";
            redisplayMenu = false;
        }

        if (redisplayMenu) {
            displayMenuOptions();
        }
    }



}


void BatchQueue::displayMenuOptions() {
    std::cout << "Please enter one of the following commands:\n\n"
        << "submit: input job data and store job in the system\n"
        << "execute: executes the program with the shortest expected executiontime\n"
        << "random: randomly executes a program stored in the system\n"
        << "quit: saves the stored programs to be executed later and exits the application\n\n";
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

                int insertResult = insertJob(estExecTime, submitterId, startCommand, resourceList);
                if (insertResult == 1) {
                    std::cout << "Failed to load inputFile: inputFile contains invalid data\n";
                    break;
                } else if (insertResult == 2) {
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
            std::cout << "The program list has been saved\n";
        }
    } else {
        outFile << saveString;
        std::cout << "The program list has been saved\n";
    }
}


void BatchQueue::submitJob() {
    if (priorityQueue->isFull()) {
        std::cout << "Cannot submit job: BatchQueue is full\n";
        return;
    }

    std::cout << "Input estExecTime\n";
    float estExecTime = getFloatInput();

    std::cout << "Input submitterId\n";
    std::string submitterId = getWordInput(8);

    std::cout << "Input startCommand\n";
    std::string startCommand = getWordInput();

    std::cout << "Input resourceList\n";
    std::string resourceList = getLineInput(80);

    int insertResult = insertJob(estExecTime, submitterId, startCommand, resourceList);
    if (insertResult == 1) {
        std::cout << "Failed to create job: invalid data submitted\n";
    } else if (insertResult == 2) {
        std::cout << "Failed to insert job: batch queue is full\n";
    } else {
        std::cout << "Job successfully submitted\n" << LINE_BREAK;
    }
}


void BatchQueue::executeNext() {
    Job* job = priorityQueue->removeMin();
    executeJob(job);
    delete job;
}


void BatchQueue::executeRandom() {
    Job* job = priorityQueue->removeRandom();
    executeJob(job);
    delete job;
}


void BatchQueue::executeJob(Job* job) {
    std::cout << "~~~ EXECUTING JOB ~~~\n"
              << "\nExecution time of program: " << job->getEstExecTime()
              << "\nSubmitter ID: " << job->getSubmitterId()
              << "\nProgram start command: " << job->getStartCommand()
              << "\nResource List: " << job->getResourceList()
              << "\n" << LINE_BREAK;
}


void BatchQueue::quitProgram() {
    std::cout << "Saving list of programs to be run\n";
//    saveBatchFile(batchFilePath);
    saveBatchFile(testOutputFile);
    std::cout << LINE_BREAK << "Thank-you for using the Batch Queue System\n"
        << LINE_BREAK;
}


int BatchQueue::insertJob(float estExecTime, std::string submitterId,
        std::string startCommand, std::string resourceList) {
    Job* job;
    try {
        job = new Job(estExecTime, submitterId, startCommand, resourceList);

    } catch (std::exception &e) {
        std::cout << e.what();
        return 1;
    }

    try {
        priorityQueue->insert(estExecTime, job);
    } catch (FullHeapException &e) {
        return 2;
    }
    return 0;
}


float BatchQueue::getFloatInput() {
    float num;
    bool badInput;

    do {
        badInput = false;
        std::cout << CMD_PROMPT;

        if (!(std::cin >> num)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            badInput = true;
            std::cout << "\nInput must be a valid positive floating point number\n";
        } else {
            if (num <= 0) {
                badInput = true;
                std::cout << "\nInput must be a valid positive floating point number\n";
            } else {
                std::cout << "\n";
            }
            std::cin.ignore();
        }
    } while (badInput == true);
    return num;
}


std::string BatchQueue::getWordInput(int maxLength) {
    bool badInput;
    std::string word;

    do
    {
        badInput = false;
        word = getLineInput(maxLength);

        if (word.length() == 0) {
            badInput = true;
            std::cout << "Input must not be left blank\n";
        } else if (std::regex_search(word, std::regex("\\s"))) {
            badInput = true;
            std::cout << "Input must be a single word with no spaces\n";
        }
    } while (badInput == true);
    return word;
}


std::string BatchQueue::getLineInput(int maxLength) {
    bool badInput;
    std::string line;

    do {
        badInput = false;
        std::cout << CMD_PROMPT;
        std::getline(std::cin, line);
        std::cout << "\n";

        if (maxLength > 0) {
            if (line.length() > maxLength) {
                badInput = true;
                std::cout << "Input must be " << maxLength << " characters or less\n";
            }
        }
    } while (badInput == true);
    return line;
}