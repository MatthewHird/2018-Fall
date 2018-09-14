//------------------------------------------------------------------------------
// @file       batch_queue.h
// @author     Matthew Hird
// @date       September 13, 2018
//
// @brief      x
//------------------------------------------------------------------------------

#ifndef ASSIGNMENT_1_BATCH_QUEUE_H
#define ASSIGNMENT_1_BATCH_QUEUE_H

#include <iostream>


class BatchQueue {
public:
    BatchQueue();

    ~BatchQueue();

    void run(std::string batchFilePath="batch.txt");

private:
};


#endif //ASSIGNMENT_1_BATCH_QUEUE_H
