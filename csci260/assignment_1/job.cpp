//------------------------------------------------------------------------------
// @file       job.cpp
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#include "job.h"


Job::Job(float estExecTime, std::string& submitterId, std::string& startCommand, std::string& resourceList)
    : estExecTime(estExecTime)
    , submitterId(submitterId)
    , startCommand(startCommand)
    , resourceList(resourceList)
{}


void Job::setEstExecTime(float estExecTime) {
    this->estExecTime = estExecTime;
}


void Job::setSubmitterId(std::string &submitterId) {
    this->submitterId = submitterId;
}


void Job::setStartCommand(std::string &startCommand) {
    this->startCommand = startCommand;
}


void Job::setResourceList(std::string &resourceList) {
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