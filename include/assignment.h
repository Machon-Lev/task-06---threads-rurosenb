#ifndef ASSIGNMENT_H
#define ASSIGNMENT_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>
#include <functional>
#include <mutex>
#include <condition_variable>

// Define the structure for messages
struct Message {
    double value;
    int threadId;
    bool isLast;
};

// Declare functions for producers and consumer
void producer(int id, std::vector<Message>& messages, std::mutex& mtx, std::condition_variable& cv);
void consumer(std::vector<Message>& messages, std::mutex& mtx, std::condition_variable& cv, int& finishedCount);

#endif // ASSIGNMENT_H
