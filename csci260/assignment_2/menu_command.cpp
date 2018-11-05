//------------------------------------------------------------------------------
// @file    menu_command.cpp
// @author  Matthew Hird
// @date    October 23, 2018
//
// @brief
//------------------------------------------------------------------------------

#include "menu_command.h"
#include <iostream>


MenuCommand::MenuCommand(char cmd, int argc, std::string* argv) {}


char MenuCommand::getCmd() {
    return ' ';
}


int MenuCommand::getArgc() {
    return 0;
}


std::string* MenuCommand::getArgv() {
    std::string* bob = nullptr;
    return bob;
}
