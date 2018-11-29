//------------------------------------------------------------------------------
// @file    social_influence_analyzer.h
// @author  Matthew Hird
// @date    November November 28, 2018
//
// @brief   The main function for the program pex3. Checks commandline
//          arguments, then starts ... controller class.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_3_SOCIAL_INFLUENCE_ANALYZER_H
#define ASSIGNMENT_3_SOCIAL_INFLUENCE_ANALYZER_H


#include "influence_graph.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <map>
#include <exception>
#include <fstream>
#include <iterator>
#include <sstream>


class SocialInfluenceAnalyzer {
public:
    /**
     * @brief
     */
    SocialInfluenceAnalyzer();

    /**
     * @brief
     */
    ~SocialInfluenceAnalyzer();

    /**
     * @brief
     * @param savefilePath
     */
    void run(std::string &savefilePath);

private:
    /**
     * @brief
     */
    void menu();

    /**
     * @brief
     */
    void displayLongMenuOptions();

    /**
     * @brief
     */
    void displayShortMenuOptions();

    /**
     * @brief
     */
    void influenceCommand();

    /**
     * @brief
     */
    void controversialCommand();

    /**
     * @brief
     * @param command
     */
    void outreachCommand(std::vector<std::string>* command);

    /**
     * @brief
     * @param command
     */
    void linkCommand(std::vector<std::string>* command);

    /**
     * @brief
     * @param command
     */
    void updateCommand(std::vector<std::string>* command);

    /**
     * @brief
     */
    void quitCommand();

    /**
     * @brief
     */
    void loadFile() throw(FailedToOpenSaveFile, InvalidSaveFileSyntax);

    /**
     * @brief
     */
    void saveFile() throw(FailedToOpenSaveFile, InvalidSaveFileSyntax);

    /**
     * @brief
     * @param arg
     * @return
     */
    int getDistance(std::string arg);

    /**
     * @brief
     * @return
     */
    std::vector<std::string>* getCommand();

    std::string savefilePath;
    InfluenceGraph* influenceGraph;
    std::string* userNameArray;


    const std::string PROGRAM_GREETING = "\n**** Thank-you for using the Social Influence Analyzer ****\n\n";
    const std::string CMD_PROMPT = ">>>  ";
    const std::string LINE_BREAK =
            "-------------------------------------------------\n\n";
};


#endif //ASSIGNMENT_3_SOCIAL_INFLUENCE_ANALYZER_H

