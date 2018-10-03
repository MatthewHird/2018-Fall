//------------------------------------------------------------------------------
// @file    job.cpp
// @author  Matthew Hird
// @date    October 4, 2018
//
// @brief   The Job data class represents a program a user wants to execute.
//          It contains various member variables that hold information related
//          to the job. Each member variable must be set within its specified
//          range or else the setter function will throw.
//------------------------------------------------------------------------------

#include <exception>
#include <regex>
#include <iostream>
#include "job.h"
#include "my_exceptions.h"


Job::Job()
    : estExecTime(1.0e30)
    , submitterId("")
    , startCommand("")
    , resourceList("")
{}


Job::Job(float estExecTime, std::string &submitterId, std::string &startCommand,
        std::string &resourceList) throw(InvalidEstExecTime, InvalidSubmitterId,
                InvalidStartCommand, InvalidResourceList)
{
    setEstExecTime(estExecTime);
    setSubmitterId(submitterId);
    setStartCommand(startCommand);
    setResourceList(resourceList);
}


void Job::setEstExecTime(float estExecTime) throw(InvalidEstExecTime) {
    if (estExecTime < 0) {
        throw InvalidEstExecTime();
    }
    this->estExecTime = estExecTime;
}


void Job::setSubmitterId(std::string &submitterId) throw(InvalidSubmitterId) {
    if (submitterId.length() > 8 || std::regex_search(submitterId, std::regex("\\s"))) {
        throw InvalidSubmitterId();
    }
    this->submitterId = submitterId;
}


void Job::setStartCommand(std::string &startCommand) throw(InvalidStartCommand) {
    if (std::regex_search(submitterId, std::regex("\\s"))){
        throw InvalidStartCommand();
    }
    this->startCommand = startCommand;
}


void Job::setResourceList(std::string &resourceList) throw(InvalidResourceList) {
    if (resourceList.length() > 80) {
        throw InvalidResourceList();
    }
    this->resourceList = resourceList;
}


float Job::getEstExecTime() {
    return estExecTime;
}


std::string Job::getSubmitterId() {
    return submitterId;
}


std::string Job::getStartCommand() {
    return startCommand;
}


std::string Job::getResourceList() {
    return resourceList;
}