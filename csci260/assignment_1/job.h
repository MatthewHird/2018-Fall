//------------------------------------------------------------------------------
// @file       job.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------
#include <iostream>

#ifndef ASSIGNMENT_1_JOB_H
#define ASSIGNMENT_1_JOB_H


class Job {
public:
    Job()= default;
    Job(float estExecTime, std::string& submitterId, std::string& startCommand,
            std::string& resourceList) throw();
    ~Job()= default;

    void setEstExecTime(float estExecTime);
    void setSubmitterId(std::string& submitterId);
    void setStartCommand(std::string& startCommand);
    void setResourceList(std::string& resourceList);

    float getEstExecTime();
    std::string getSubmitterId();
    std::string getStartCommand();
    std::string getResourceList();

private:
    float estExecTime;
    std::string submitterId; // max length 8 chars, single word
    std::string startCommand; // single word
    std::string resourceList; // max length 80 chars
};


#endif //ASSIGNMENT_1_JOB_H
