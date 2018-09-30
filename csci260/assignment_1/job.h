//------------------------------------------------------------------------------
// @file       job.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_JOB_H
#define ASSIGNMENT_1_JOB_H

#include <iostream>
#include "my_exceptions.h"


class Job {
public:
    Job();
    Job(float estExecTime, std::string &submitterId, std::string &startCommand, std::string &resourceList)
            throw(InvalidEstExecTime, InvalidSubmitterId,
                    InvalidStartCommand, InvalidResourceList);
    ~Job()= default;

    void setEstExecTime(float estExecTime) throw(InvalidEstExecTime);
    void setSubmitterId(std::string &submitterId) throw(InvalidSubmitterId);
    void setStartCommand(std::string &startCommand) throw(InvalidStartCommand);
    void setResourceList(std::string &resourceList) throw(InvalidResourceList);

    float getEstExecTime();
    std::string getSubmitterId();
    std::string getStartCommand();
    std::string getResourceList();

private:
    float estExecTime; // positive float
    std::string submitterId; // max length 8 chars, single word
    std::string startCommand; // single word
    std::string resourceList; // max length 80 chars
};

#endif //ASSIGNMENT_1_JOB_H
