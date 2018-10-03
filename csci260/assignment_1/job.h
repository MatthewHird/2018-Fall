//------------------------------------------------------------------------------
// @file    job.h
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   The Job data class represents a program a user wants to execute.
//          It contains various member variables that hold information related
//          to the job. Each member variable must be set within its specified
//          range or else the setter function will throw.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_JOB_H
#define ASSIGNMENT_1_JOB_H

#include <iostream>
#include "my_exceptions.h"


class Job {
public:
    /**
     * @brief Default class constructor. estExecTime = 1.0e30,
     */
    Job();

    /**
     * @brief Parameterized constructor.
     *
     * @param estExecTime   The estimated execution time value.
     * @param submitterId   The submitting user's ID.
     * @param startCommand  The job's start command.
     * @param resourceList  The job's required resources list.
     *
     * @throws InvalidEstExecTime   if estExecTime <= 0.
     * @throws InvalidSubmitterId   if submitterId length > 8 characters or
     *                              contains whitespace.
     * @throws InvalidStartCommand  if startCommand contains whitespace.
     * @throws InvalidResourceList  if resourceList length > 80 characters.
     *
     */
    Job(float estExecTime, std::string &submitterId, std::string &startCommand, std::string &resourceList)
            throw(InvalidEstExecTime, InvalidSubmitterId,
                    InvalidStartCommand, InvalidResourceList);

    /**
     * @brief Class destructor.
     */
    ~Job()= default;

    /**
     * @brief Sets the estimated execution time member variable.
     *
     * @param estExecTime   The estimated execution time value.
     *
     * @throws InvalidEstExecTime   if estExecTime <= 0.
     */
    void setEstExecTime(float estExecTime) throw(InvalidEstExecTime);

    /**
     * @brief Sets the submitting user's ID member variable.
     *
     * @param submitterId   The submitting user's ID.
     *
     * @throws InvalidSubmitterId   if submitterId length > 8 characters or
     *                              contains whitespace.
     */
    void setSubmitterId(std::string &submitterId) throw(InvalidSubmitterId);

    /**
     * @brief Sets the job's start command member variable.
     *
     * @param startCommand  The job's start command.
     *
     * @throws InvalidStartCommand  if startCommand contains whitespace.
     */
    void setStartCommand(std::string &startCommand) throw(InvalidStartCommand);

    /**
     * @brief Sets the job's required resources list.
     *
     * @param resourceList  The job's required resources list.
     *
     * @throws InvalidResourceList  if resourceList length > 80 characters.
     */
    void setResourceList(std::string &resourceList) throw(InvalidResourceList);

    /**
     * @return The value of estExecTime member variable.
     */
    float getEstExecTime();

    /**
     * @return The value of submitterId member variable.
     */
    std::string getSubmitterId();

    /**
     * @return The value of startCommand member variable.
     */
    std::string getStartCommand();

    /**
     * @return The value of resourceList member variable.
     */
    std::string getResourceList();

private:
    float estExecTime; // positive float
    std::string submitterId; // max length 8 chars, single word
    std::string startCommand; // single word
    std::string resourceList; // max length 80 chars
};

#endif //ASSIGNMENT_1_JOB_H
