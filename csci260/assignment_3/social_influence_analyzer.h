//------------------------------------------------------------------------------
// @file    social_influence_analyzer.h
// @author  Matthew Hird
// @date    November November 28, 2018
//
// @brief   Program that allows a user to input commands to interact with a 
//          social influence graph. This graph contains a number of users, and 
//          connects them based on the influence each user has other users. The
//          edges of the graph are both directional and weighted (edges have a 
//          value of 1 for positive influence and -1 for negative influences).
//          The program is started by calling the run(std::string filePath) 
//          public method. When the program starts, the file at filePath is read
//          and used to populate the graph. When the program is exited through
//          the "quit" command, the data contained in the graph is save in 
//          filePath, overwriting the file. 
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
     * @brief Default class constructor.
     */
    SocialInfluenceAnalyzer();

    /**
     * @brief Class destructor.
     */
    ~SocialInfluenceAnalyzer();

    /**
     * @brief Public entry point of the program. Saves the savefilePath.
     * @param savefilePath  The path of the file to be loaded. The file's 
     *                      contents are used to populate the influence graph.
     *                      When the program exits, the contents of the 
     *                      influence graph are saved to the same filepath 
     *                      (file will be overwritten).
     */
    void run(std::string &savefilePath);

private:
    /**
     * @brief Main control hub of the program. Loads savefile on startup, 
     *         then prompts the user to enter commands until the "quit" command
     *         is entered. Saves data into savefile on exit.
     */
    void menu();

    /**
     * @brief Displays the command menu with full descriptions of each command.
     */
    void displayLongMenuOptions();

    /**
     * @brief Displays the command menu with just the command name and arguments
     *        for each command.
     */
    void displayShortMenuOptions();

    /**
     * @brief Lists the user name, and number of links, of the user with the 
     *        most positive direct links. Command entered: "influence"
     */
    void influenceCommand();

    /**
     * @brief Lists the user name, and number of links, of the user with the 
     *        most direct links, both positive and negative. Command entered:
     *        "controversial"
     */
    void controversialCommand();

    /**
     * @brief Lists the number of users influenced by this user, both directly
     *        and indirectly, positively and negatively.
     * @param command   The command name and arguments entered by the user.
     *                  Command entered: "outreach <username>"
     */
    void outreachCommand(std::vector<std::string>* command);

    /**
     * @brief Lists the shortest path of positive links from <user1> to <user2>.
     * @param command   The command name and arguments entered by the user.
     *                  Command entered: "link <user1> <user2>"
     */
    void linkCommand(std::vector<std::string>* command);

    /**
     * @brief Updates the link between <user1> and <user2>, setting the distance
     *        to <distance>, then displays a confirmation message.
     * @param command   The command name and arguments entered by the user.
     *                  Command entered: "update <user1> <user2> <distance>"
     */
    void updateCommand(std::vector<std::string>* command);

    /**
     * @brief Saves the data in the graph to savefile, and exits the program.
     */
    void quitCommand();

    /**
     * @brief Load the savefile listed in the savefilePath member variable.
     * @throws FailedToOpenSaveFile     If savefile cannot be opened.
     * @throws InvalidSaveFileSyntax    If there are any syntax errors in the
     *                                  savefile.
     */
    void loadFile() throw(FailedToOpenSaveFile, InvalidSaveFileSyntax);

    /**
     * @brief Saves the data stored in the influence graph to the savefile
     *        listed in the savefilePath member variable.
     * @throws FailedToOpenSaveFile     If savefile cannot be opened.
     * @throws InvalidSaveFileSyntax    If there are any syntax errors in the
     *                                  savefile.
     */
    void saveFile() throw(FailedToOpenSaveFile, InvalidSaveFileSyntax);

    /**
     * @brief Converts a string to an distance value.
     * @param arg   The string to be converted.
     * @return If arg is "-1", "0", or "1", -1, 0, or 1 repectivly will be 
     *         returned. If arg can be converted to an int, but the int is out 
     *         of range, -3 is returned. If arg cannot be converted to an 
     *         integer, -2 is returned.
     */
    int getDistance(std::string arg);

    /**
     * @brief Promptes user to enter a command. Reads a full line, and splits
     *        the string using whitespace as a delimitter.
     * @return A vector containing the command and arguments as entries. Any
     *         leading, trailing, or internal whitespae will not be included in
     *         any arguments. If user entry is blank or only contains 
     *         whitespace, a vector with a single entry "No command entered" is 
     *         returned. 
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

