//------------------------------------------------------------------------------
// @file    influence_graph.h
// @author  Matthew Hird
// @date    November November 28, 2018
//
// @brief   A weighted, directional graph used to store and manipulate social
//          influence data. Each vertex in the graph is a username, and the 
//          edges represent the positive or negative influence the user has on
//          another user.
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
     * @brief Parameterized class constructor.
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
     * @brief Calculates the number of direct positive links a users has.
     * @param userName          The name of the user.
     * @throws InvalidUserName  If userName is not in the system.
     * @return The number of positive links the user has.
     */
    int directPositive(std::string &userName) throw(InvalidUserName);

    /**
     * @brief Calculates the number of direct positive or negative links a user 
     *        has.
     * @param userName          The name of the user.
     * @throws InvalidUserName  If the user is not in the system.
     * @return The number of positive and negative links the user has. 
     */
    int directPosOrNeg(std::string &userName) throw(InvalidUserName);

    /**
     * @brief Calculates the number of other users the the user has an influence
     *        on, both positively and negatively, and directly or indirectly.
     * @param userName          The name of the user.
     * @throws InvalidUserName  If the user is not in the system.
     * @return The number of users influenced by this user.
     */
    int userOutreach(std::string &userName) throw(InvalidUserName);

    /**
     * @brief Finds the shortest path of positive links from user1 to user2.
     * @param user1 The source user.
     * @param user2 The destination user.
     * @throws InvalidUserName      If a username is not in the system.
     * @throws InvalidPathToSelf    If user1 and user2 are the same.
     * @return Returns the names of the users in the link path, including the 
     *         source and destination users. Returns an empty vector if no path
     *         exists from user1 to user2.
     */
    std::vector<std::string> positiveLink(std::string &user1, std::string &user2)
            throw(InvalidUserName, InvalidPathToSelf);

    /**
     * @brief Compiles the data needed to recreate the graph and returns it as 
     *        a string.  
     * @return First line contains an integer (call it n) representing 
     *        the number of users. The following n lines are the names of all of
     *        the users in the system. The rest of the lines contain the data
     *        for a single edge. They are each in the form 
     *        "<user1>\t<user2>\t<distance>\n".
     */
    std::string getGraphSaveData();

    /**
     * @brief The number of users in the system.
     * @return Number of user vertices in the graph.
     */
    int getUserCount();

private:
    /**
     * @brief Checks to see if userName is in the system.
     * @param userName  The name of the user being checked.
     * @return True if userName is in the system.
     */
    bool isUser(std::string &userName);

    /**
     * @brief Finds the unique index associated with the unique userName.
     * @param userName          The username whose index is being fetched.
     * @throws InvalidUserName  If userName is not in the system.
     * @return The index associated with userName.
     */
    int getIndex(std::string &userName) throw(InvalidUserName);

    /**
     * @brief Resets the entries of the visited member array to false.
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
