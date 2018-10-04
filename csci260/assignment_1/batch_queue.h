//------------------------------------------------------------------------------
// @file    batch_queue.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   A program meant to simulate a batch queue. The program loads jobs
//          from a save file into a priority queue to be executed later. The
//          user enters commands to control the program. Submit lets the user
//          enter data for a job to be added to the queue. Execute removes the
//          job with the shortest execution time from the queue and simulates
//          executing it. Random removes a random job from the queue and
//          simulates executing it. Quit stores the data of any jobs remaining
//          in the queue into a save file to be load next time the batch queue
//          program is run, then terminates the program.
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
     * @brief Parameterized class constructor.
     *
     * @param queueCapacity Maximum number of Jobs the batch queue can hold.
     */
    explicit BatchQueue(int queueCapacity=10);

    /**
     * @brief Class destructor.
     */
    ~BatchQueue();

    /**
     * @brief Public start point of the program. Loads saved programs into the
     *        queue from "batch.txt", then invokes the menu.
     */
    void run();

private:
    /**
     * @brief Displays a list of commands, prompts the user to enter a command,
     *        then invokes a subroutine based on the command.
     */
    void menu();

    /**
     * @brief Displays the list of main menu commands.
     */
    void displayMenuOptions();

    /**
     * @brief Reads contents of save file, uses the data to create Job objects,
     *        then stores the Job objects the priority queue.
     *
     * @param loadFilePath  The save file to load from.
     */
    void loadBatchFile(std::string &loadFilePath);

    /**
     * @brief Removes the Jobs currently in the priority queue, one by one, and
     *        writes their data into a save file to be loaded next time the
     *        program launches.
     *
     * @param saveFilePath  The save file to be written to.
     */
    void saveBatchFile(std::string &saveFilePath);

    /**
     * @brief Prompts user to input data for a Job they want to execute. The Job
     *        is then added to the priority queue to be executed later.
     */
    void submitJob();

    /**
     * @brief The Job with the shortest estimated execution time is removed from
     *        the priority queue and is executed.
     */
    void executeNext();

    /**
     * @brief A random Job is removed from the priority queue and is executed.
     *        This is to give jobs with long execution times a chance to be run.
     */
    void executeRandom();

    /**
     * @brief Displays the contents of a job to std::cout. Meant to simulate the
     *        execution of a Job.
     *
     * @param job   The Job to be executed (displayed).
     */
    void executeJob(Job* job);

    /**
     * @brief Stores any Jobs remaining in the priority queue into a save file,
     *        then terminates the program.
     */
    void quitProgram();

    /**
     * @brief Takes in data values corresponding to the data fields of a Job
     *        object. Attempts to create a Job object from these data values.
     *        Then attempts to insert the Job into the priority queue.
     *
     * @param estExecTime
     * @param submitterId
     * @param startCommand
     * @param resourceList
     *
     * @return 0: Job is successfully created and inserted into priority queue.
     *         1: Failed to create Job object due to invalid data.
     *         2: Failed to insert Job object into priority queue because the
     *            priority queue is full.
     */
    int insertJob(float estExecTime, std::string submitterId,
            std::string startCommand, std::string resourceList);

    /**
     * @brief Prompts user to input a valid positive floating point value.
     *        Displays error message if the value is invalid and continues to
     *        prompt the user until a valid value is entered.
     *
     * @return Positive floating point number input by the user.
     */
    float getFloatInput();

    /**
     * @brief Prompts user to input a word (non-empty string containing no
     *        spaces) that is within the max character length. Displays error
     *        message if the string is invalid and continues to prompt the user
     *        until a valid value is entered.
     *
     * @param maxLength The maximum number of characters the entered string may
     *                  contain.
     *
     * @return The non-empty string containing no spaces entered by the user.
     */
    std::string getWordInput(int maxLength=0);

    /**
     * @brief Prompts user to input a string that is within the max character
     *        length. This string may contain spaces or be left blank. Displays
     *        error message if the string is invalid and continues to prompt the
     *        user until a valid value is entered.
     *
     * @param maxLength The maximum number of characters the entered string may
     *                  contain. If maxLength <= 0, then there is no maximum
     *                  character length.
     *
     * @return The string within the max character length entered by the user.
     */
    std::string getLineInput(int maxLength=0);

    const std::string CMD_PROMPT = ">>>  ";
    const std::string LINE_BREAK =
            "-------------------------------------------------\n\n";

    int queueCapacity;
    std::string batchFilePath = "batch.txt";
    std::string testOutputFile = "batch_TEST.txt";
    PriorityQueue<float,Job>* priorityQueue;
};

#endif //ASSIGNMENT_1_BATCH_QUEUE_H
