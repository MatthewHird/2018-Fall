//------------------------------------------------------------------------------
// @file    influence_graph.cpp
// @author  Matthew Hird
// @date    November November 28, 2018
//
// @brief   A weighted, directional graph used to store and manipulate social
//          influence data. Each vertex in the graph is a username, and the 
//          edges represent the positive or negative influence the user has on
//          another user.
//------------------------------------------------------------------------------

#include "influence_graph.h"


InfluenceGraph::InfluenceGraph(int arrayLength, std::string* userNameArray) {
    vertexCount = arrayLength;
    visited = new bool[vertexCount];
    this->userNameArray = userNameArray;
    adjacencyList = new std::list<Edge>[vertexCount];

    userIndexMap = new std::map<std::string,int>();
    for (int i = 0; i < vertexCount; i++) {
        userIndexMap->emplace(userNameArray[i], i);
    }
}


InfluenceGraph::~InfluenceGraph() {
    delete userIndexMap;
    delete []adjacencyList;
    delete []userNameArray;
    delete []visited;
}


void InfluenceGraph::modifyEdge(std::string &user1, std::string &user2, int distance)
        throw(InvalidUserName, InvalidDistance, InvalidEdgeToSelf) {
    int user1Index = getIndex(user1);
    int user2Index = getIndex(user2);

    if (distance < -1 || distance > 1) {
        throw InvalidDistance();
    }

    for (auto &edge : adjacencyList[user1Index]) {
        if (edge.adjacentVertex == user2Index) {
            if (edge.distance == distance) {
                throw InvalidEdgeToSelf(user1);
            } else if (distance == 0) {
                adjacencyList[user1Index].remove(edge);
            } else {
                edge.distance = distance;
            }
            return;
        }
    }

    if (distance == 0) {
        return;
    }

    adjacencyList[user1Index].emplace_back(user2Index, distance);
}


int InfluenceGraph::directPositive(std::string &userName) throw(InvalidUserName) {
    int userIndex = getIndex(userName);
    int influenceCount = 0;

    for (auto &edge : adjacencyList[userIndex]) {
        if (edge.distance == 1) {
            influenceCount++;
        }
    }
    return influenceCount;
}


int InfluenceGraph::directPosOrNeg(std::string &userName) throw(InvalidUserName) {
    int userIndex = getIndex(userName);

    return int(adjacencyList[userIndex].size());
}


int InfluenceGraph::userOutreach(std::string &userName) throw(InvalidUserName) {
    int userIndex = getIndex(userName);

    resetVisited();
    std::queue<int> queue;

    queue.push(userIndex);
    visited[userIndex] = true;

    int influenceCount = 0;
    std::list<Edge>::iterator edge;

    while(!queue.empty()) {
        userIndex = queue.front();
        queue.pop();

        for (edge = adjacencyList[userIndex].begin(); edge != adjacencyList[userIndex].end(); edge++) {
            int i = edge->adjacentVertex;
            if (!visited[i]) {
                queue.push(i);
                influenceCount++;
                visited[i] = true;
            }
        }
    }

    return influenceCount;
}


std::vector<std::string> InfluenceGraph::positiveLink(std::string &user1, std::string &user2) throw(InvalidUserName, InvalidPathToSelf) {
    std::vector<std::string> shortestPath;
    int currentIndex = getIndex(user1);
    int destinationIndex = getIndex(user2);

    if (currentIndex == destinationIndex) {
        throw InvalidPathToSelf(user1);
    }

    int prev[vertexCount];
    for (int i = 0; i < vertexCount; i ++) {
        prev[i] = -1;
    }

    resetVisited();
    std::queue<int> queue;
    std::list<Edge>::iterator edge;

    queue.push(currentIndex);
    visited[currentIndex] = true;

    while(!queue.empty()) {
        currentIndex = queue.front();
        queue.pop();

        for (edge = adjacencyList[currentIndex].begin();
                edge != adjacencyList[currentIndex].end(); edge++) {
            int i = edge->adjacentVertex;
            if (edge->distance == 1 && !visited[i]) {
                queue.push(i);
                prev[i] = currentIndex;
                visited[i] = true;
            }
        }
    }

    if (prev[destinationIndex] == -1) {
        return shortestPath;
    }

    std::stack<int> stack;
    while (destinationIndex != -1) {
        stack.push(destinationIndex);
        destinationIndex = prev[destinationIndex];
    }

    while (!stack.empty()) {
        shortestPath.emplace_back(userNameArray[stack.top()]);
        stack.pop();
    }

    return shortestPath;
}


std::string InfluenceGraph::getGraphSaveData() {
    std::string saveData;

    saveData.append(std::to_string(vertexCount));
    saveData.append("\n");

    for (int i = 0; i < vertexCount; i++) {
        saveData.append(userNameArray[i]);
        saveData.append("\n");
    }

    std::list<Edge>::iterator edge;

    for (int i = 0; i < vertexCount; i++) {
        for (edge = adjacencyList[i].begin(); edge != adjacencyList[i].end(); edge++) {
            saveData.append(userNameArray[i]);
            saveData.append("\t");
            saveData.append(userNameArray[edge->adjacentVertex]);
            saveData.append("\t");
            saveData.append(std::to_string(edge->distance));
            saveData.append("\n");
        }
    }

    return saveData;
}


int InfluenceGraph::getUserCount() {
    return vertexCount;
}


bool InfluenceGraph::isUser(std::string &userName) {
    return userIndexMap->count(userName) != 0;
}


int InfluenceGraph::getIndex(std::string &userName) throw(InvalidUserName) {
    if (!isUser(userName)) {
        throw InvalidUserName(userName);
    }
    return userIndexMap->at(userName);
}


void InfluenceGraph::resetVisited() {
    for (int i = 0; i < vertexCount; i++) {
        visited[i] = false;
    }
}
