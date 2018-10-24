//------------------------------------------------------------------------------
// @file    menu_command.h
// @author  Matthew Hird
// @date    October 23, 2018
//
// @brief
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_2_MENU_COMMAND_H
#define ASSIGNMENT_2_MENU_COMMAND_H


#include <string>

class MenuCommand {
public:
    /**
     * @brief
     *
     * @param cmd
     * @param argc
     * @param argv
     */
    MenuCommand(char cmd, int argc, std::string* argv);

    /**
     * @brief
     */
    ~MenuCommand()= default;

    /**
     * @brief
     *
     * @return
     */
    char getCmd();

    /**
     * @brief
     *
     * @return
     */
    int getArgc();

    /**
     * @brief
     *
     * @return
     */
    std::string* getArgv();

private:
    char cmd;
    int argc;
    std::string* argv;
};


#endif //ASSIGNMENT_2_MENU_COMMAND_H
