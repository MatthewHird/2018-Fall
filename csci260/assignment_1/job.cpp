//------------------------------------------------------------------------------
// @file       job.cpp
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#include <exception>
#include <regex>
#include "job.h"


Job::Job(float estExecTime, std::string& submitterId, std::string& startCommand, std::string& resourceList) throw()
{
    setEstExecTime(estExecTime);
    setSubmitterId(submitterId);
    setStartCommand(startCommand);
    setResourceList(resourceList);
}


void Job::setEstExecTime(float estExecTime) {
    this->estExecTime = estExecTime;
}


void Job::setSubmitterId(std::string &submitterId) {
    if (submitterId.length() > 8 || std::regex_search(submitterId, std::regex("\\s"))) {
        // throw invalid submitterId exception
    }
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