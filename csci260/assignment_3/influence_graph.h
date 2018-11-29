//------------------------------------------------------------------------------
// @file    influence_graph.h
// @author  Matthew Hird
// @date    November November 28, 2018
//
// @brief   The main function for the program pex3. Checks commandline
//          arguments, then starts ... controller class.
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_3_INFLUENCE_GRAPH_H
#define ASSIGNMENT_3_INFLUENCE_GRAPH_H

#include <iostream>
#include <map>
#include <queue>
#include <list>
#include <stack>
#include <tuple>
#include <vector>
#include <exception>
#include "my_exceptions.h"


class InfluenceGraph {
public:
    /**
     * @brief Parameterized class constructor
     * @param arrayLength   The number of elements in userNameArray.
     * @param userNameArray An array of the user names to be graphed.
     */
    InfluenceGraph(int arrayLength, std::string* userNameArray);

    /**
     * @brief Class destructor.
     */
    ~InfluenceGraph();

    /**
     * @brief Adds a directional edge with a distance value from user1 to user2.
     * @param user1     The vertex the edge is coming from.
     * @param user2     The vertex the edge is going to.
     * @param distance  A value of 1 represents positive influence, and -1
     *                  represents a negative influence. 0 represents no
     *                  influence, and will not create an edge.
     * @throws InvalidUserName      If user1 or user2 are not in the system.
     * @throws InvalidDistance      If distance > 1 or distance < -1.
     * @throws InvalidEdgeToSelf    If user1 = user2.
     */
    void modifyEdge(std::string &user1, std::string &user2, int distance)
            throw(InvalidUserName, InvalidDistance, InvalidEdgeToSelf);

    /**
     * @brief
     * @param userName
     * @throws InvalidUserName
     * @return
     */
    int directPositive(std::string &userName) throw(InvalidUserName);

    /**
     * @brief
     * @param userName
     * @throws InvalidUserName
     * @return
     */
    int directPosOrNeg(std::string &userName) throw(InvalidUserName);

    /**
     * @brief
     * @param userName
     * @throws InvalidUserName
     * @return
     */
    int userOutreach(std::string &userName) throw(InvalidUserName);

    /**
     * @brief
     * @param user1
     * @param user2
     * @throws InvalidUserName
     * @throws InvalidPathToSelf
     * @return
     */
    std::vector<std::string> positiveLink(std::string &user1, std::string &user2)
            throw(InvalidUserName, InvalidPathToSelf);

    /**
     * @brief
     * @return
     */
    std::string getGraphSaveData();

    /**
     * @brief
     * @return
     */
    int getUserCount();

private:
    /**
     * @brief
     * @param userName
     * @return
     */
    bool isUser(std::string &userName);

    /**
     * @brief
     * @param userName
     * @throws InvalidUserName
     * @return
     */
    int getIndex(std::string &userName) throw(InvalidUserName);

    /**
     * @brief
     */
    void resetVisited();

    class Edge {
    public:
        int adjacentVertex;
        int distance;

        Edge(int adjacentVertex, int distance)
            : adjacentVertex(adjacentVertex)
            , distance(distance)
        {}

        bool operator==(const Edge &other) {
            bool equal = true;
            if (adjacentVertex != other.adjacentVertex) {
                equal = false;
            } else if (distance != other.distance) {
                equal = false;
            }
            return equal;
        };
    };

    int vertexCount;
    bool* visited;
    std::map<std::string,int>* userIndexMap;
    std::string* userNameArray;
    std::list<Edge>* adjacencyList;
};


#endif //ASSIGNMENT_3_INFLUENCE_GRAPH_H
