//------------------------------------------------------------------------------
// @file    social_influence_analyzer.cpp
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

#include "social_influence_analyzer.h"


SocialInfluenceAnalyzer::SocialInfluenceAnalyzer() {
    influenceGraph = nullptr;
    userNameArray = nullptr;
}


SocialInfluenceAnalyzer::~SocialInfluenceAnalyzer() {
    delete influenceGraph;
}


void SocialInfluenceAnalyzer::run(std::string &savefilePath) {
    this->savefilePath = savefilePath;
    menu();
}


void SocialInfluenceAnalyzer::menu() {
    std::cout << PROGRAM_GREETING;
    bool terminate = false;

    try {
        loadFile();
        displayLongMenuOptions();
    } catch (FailedToOpenSaveFile &e) {
        std::cout << "Error: Failed to open savefile; program will be terminated\n\n";
        terminate = true;
    } catch (InvalidSaveFileSyntax &e) {
        std::cout << "Error: Failed to load savefile; program will be terminated\n"
                     "    Please check savefile for syntax errors\n\n";
        terminate = true;
    }

    while(!terminate) {
        bool redisplayMenu = true;

        std::vector<std::string>* command = getCommand();
        std::string cmd = command->at(0);
        std::cout << "\n";

        if (cmd == "influence") {
            influenceCommand();
        } else if (cmd == "controversial") {
            controversialCommand();
        } else if (cmd == "outreach") {
            outreachCommand(command);
        } else if (cmd == "link") {
            linkCommand(command);
        } else if (cmd == "update") {
            updateCommand(command);
        } else if (cmd == "help") {
            displayLongMenuOptions();
            redisplayMenu = false;
        } else if (cmd == "quit") {
            quitCommand();
            terminate = true;
            redisplayMenu = false;
        } else {
            std::cout << "Invalid command: please try again\n";
            redisplayMenu = false;
        }

        if (redisplayMenu) {
            displayShortMenuOptions();
        }
    }
}


void SocialInfluenceAnalyzer::displayLongMenuOptions() {
    std::cout <<
    "Please enter one of the following commands:\n\n"
    "influence\n"
    "    list the name of the user who can directly and positively influence the\n"
    "    greatest number of users\n"
    "controversial\n"
    "    list the name of the user who can directly influence the greatest number of\n"
    "    users, either positively or negatively\n"
    "outreach <username>\n"
    "    count the number of users <username> can influence, whether directly or\n"
    "    indirectly, positively or negatively\n"
    "link <user1> <user2>\n"
    "    list the shortest positive influence link from <user1> to <user2>\n"
    "    (this lists the names of all the users in this link)\n"
    "update <user1> <user2> <distance>\n"
    "    update the influence distance from <user1> to <user2> with <distance>\n"
    "help\n"
    "    displays full menu options with explanations (this menu)\n"
    "quit\n"
    "    quit the system and write the updated graph data back to original savefile\n\n";
}


void SocialInfluenceAnalyzer::displayShortMenuOptions() {
    std::cout <<
              "Please enter one of the following commands:\n\n"
              "influence\n"
              "controversial\n"
              "outreach <username>\n"
              "link <user1> <user2>\n"
              "update <user1> <user2> <distance>\n"
              "help\n"
              "quit\n\n";
}


void SocialInfluenceAnalyzer::influenceCommand() {
    try {
        std::string maxUser;
        int maxInfluence = 0;
        int userCount = influenceGraph->getUserCount();

        for (int i = 0; i < userCount; i++) {
            int count = influenceGraph->directPositive(userNameArray[i]);
            if (count > maxInfluence) {
                maxInfluence = count;
                maxUser = userNameArray[i];
            }
        }

        if (maxInfluence == 0) {
            std::cout << "No user has any direct positive influence links\n" << LINE_BREAK;
        } else {
            std::cout << "The most influential user is " << maxUser
                      << " with " << maxInfluence << " positive links\n" << LINE_BREAK;
        }
    } catch (InvalidUserName &e) {
        std::cout << "Invalid username: " << e.getInvalidName() << "\n\n";
    }
}


void SocialInfluenceAnalyzer::controversialCommand() {
    try {
        std::string maxUser;
        int maxInfluence = 0;
        int userCount = influenceGraph->getUserCount();

        for (int i = 0; i < userCount; i++) {
            int count = influenceGraph->directPosOrNeg(userNameArray[i]);
            if (count > maxInfluence) {
                maxInfluence = count;
                maxUser = userNameArray[i];
            }
        }

        if (maxInfluence == 0) {
            std::cout << "No user has any direct positive or negative influence links\n" << LINE_BREAK;
        } else {
            std::cout << "The most controversial user is " << maxUser
                      << " with " << maxInfluence << " positive or negative links\n" << LINE_BREAK;
        }
    } catch (InvalidUserName &e) {
        std::cout << "Invalid username: " << e.getInvalidName() << "\n\n";
    }
}


void SocialInfluenceAnalyzer::outreachCommand(std::vector<std::string>* command) {
    try {
        if (command->size() < 2) {
        std::cout << "Invalid use of \"outreach\" command: too few arguments\n"
                     "Argument one must be a user in the system\n\n";
        } else {
            std::string user = command->at(1);
            int influence;

            influence = influenceGraph->userOutreach(user);

            std::cout << user << " can directly or indirectly influence " << std::to_string(influence)
                  << " users\n" << LINE_BREAK;
        }
    } catch (InvalidUserName &e) {
        std::cout << "Invalid username: " << e.getInvalidName() << "\n\n";
    }
}


void SocialInfluenceAnalyzer::linkCommand(std::vector<std::string>* command) {
    try {
        if (command->size() < 3) {
            std::cout << "Invalid use of \"link\" command: too few arguments\n\n";
        } else {
            std::string user1 = command->at(1);
            std::string user2 = command->at(2);
            std::vector<std::string> path = influenceGraph->positiveLink(user1, user2);
            unsigned long pathLength = path.size();

            if (path.empty()) {
                std::cout << "No positive influence link exists between " << user1
                          << " and " << user2 << "\n" << LINE_BREAK;
            } else {
                std::cout << "Shortest positive influence link from " << user1
                          << " to " << user2 << ":\n    " << user1;

                for (unsigned long i = 1; i < pathLength; i++) {
                    if (i % 4 == 0) {
                        std::cout << "\n   ";
                    }
                    std::cout << " -> " << path.at(i);
                }
                std::cout << "\n" << LINE_BREAK;
            }
        }
    } catch (InvalidUserName &e) {
        std::cout << "Invalid username: " << e.getInvalidName() << "\n\n";
    } catch (InvalidPathToSelf &e) {
        std::cout << "Invalid path: user1 and user2 both named " << e.getInvalidName() << "\n\n";
    }
}


void SocialInfluenceAnalyzer::updateCommand(std::vector<std::string>* command) {
    try {
        if (command->size() < 4) {
            std::cout << "Invalid use of \"update\" command: too few arguments\n\n";
        } else {
            std::string user1 = command->at(1);
            std::string user2 = command->at(2);
            int distance = getDistance(command->at(3));
            influenceGraph->modifyEdge(user1, user2, distance);
            std::cout << "Successfully updated influence distance between\n"
                      << user1 << " and " << user2 << " to a value of "
                      << distance << "\n" << LINE_BREAK;
        }
    } catch (InvalidUserName &e) {
        std::cout << "Invalid username: " << e.getInvalidName() << "\n\n";
    } catch (InvalidDistance &e) {
        std::cout << "Invalid distance: distance must be an integer in the range of -1 to 1\n\n";
    } catch (InvalidEdgeToSelf &e) {
        std::cout << "Invalid edge: user1 and user2 both named " << e.getInvalidName() << "\n\n";
    }
}


void SocialInfluenceAnalyzer::quitCommand() {
    std::cout << LINE_BREAK << "Saving graph data to " << savefilePath << "...\n";
    try {
        saveFile();
        std::cout << "Graph successfully saved\n\n";
    } catch (FailedToOpenSaveFile &e) {
        std::cout << "Error: Failed to open savefile\n"
                     "    Graph data will not be saved\n";
    }
    std::cout << LINE_BREAK << "**** Thank-you for using the Social Influence Analyzer ****\n\n";
}


void SocialInfluenceAnalyzer::loadFile() throw(FailedToOpenSaveFile, InvalidSaveFileSyntax) {
    int vertexCount;
    std::ifstream fin;

    fin.open(savefilePath.c_str());

    if (fin.fail()) {
        throw FailedToOpenSaveFile();
    }

    try {
        fin >> vertexCount;
        fin.ignore();
        userNameArray = new std::string[vertexCount];

        for (int i = 0; i < vertexCount; i++) {
            std::string userName;
            getline(fin, userName);
            userNameArray[i] = userName;
        }

        influenceGraph = new InfluenceGraph(vertexCount, userNameArray);

        while (true) {
            std::string nextLine;
            getline(fin, nextLine);

            if (fin.eof()) {
                break;
            }
            std::istringstream iss(nextLine);
            std::vector<std::string> args(std::istream_iterator<std::string>{iss},
                                          std::istream_iterator<std::string>());

            int distance = getDistance(args[2]);
            influenceGraph->modifyEdge(args[0], args[1], distance);

        }
        fin.close();
    } catch (InvalidUserName &e) {
        std::cout << "Error: Invalid username " << e.getInvalidName() << "\n";
        throw InvalidSaveFileSyntax();
    } catch (InvalidDistance &e) {
        std::cout << "Error: Invalid distance in savefile\n"
                     "    Distances must be integers in the range of -1 to 1\n";
        throw InvalidSaveFileSyntax();
    } catch (InvalidEdgeToSelf &e) {
        std::cout << "Error: Invalid data in save file\n    "
                  << e.getInvalidName() << " has an edge to itself\n";
        throw InvalidSaveFileSyntax();
    } catch (std::exception &e) {
        std::cout << "Error: An unexpected error has occurred while loading savefile\n";
        throw InvalidSaveFileSyntax();
    }
}


void SocialInfluenceAnalyzer::saveFile() throw(FailedToOpenSaveFile, InvalidSaveFileSyntax) {
    std::ofstream fout;

    fout.open(savefilePath.c_str());

    if (fout.fail()) {
        throw FailedToOpenSaveFile();
    }

    try {
        fout << influenceGraph->getGraphSaveData();
        fout.close();
    } catch (std::exception &e) {
        std::cout << "Error: An unexpected error has occurred while writing to savefile\n";
        throw InvalidSaveFileSyntax();
    }
}


int SocialInfluenceAnalyzer::getDistance(std::string arg) {
    int distance;

    try {
        distance = std::stoi(arg);
    } catch (std::invalid_argument &e) {
        distance = -2;
    } catch (std::out_of_range &e) {
        distance = -3;
    }

    return distance;
}


std::vector<std::string>* SocialInfluenceAnalyzer::getCommand() {
    auto command = new std::vector<std::string>();
    std::string user_string;
    std::string argument;

    std::cout << CMD_PROMPT;
    std::getline(std::cin, user_string);

    if (user_string.length() == 0) {
        command->emplace_back("No command entered");
        return command;
    }

    for (char c : user_string) {
        if (c == ' ') {
            if (!argument.empty()) {
                command->push_back(argument);
                argument.clear();
            }
        } else {
            argument += std::string(1, c);
        }
    }

    if (!argument.empty()) {
        command->push_back(argument);
    }

    return command;
}
