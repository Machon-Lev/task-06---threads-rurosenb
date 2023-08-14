#include "assignment.h"

// Implement the producer function
void producer(int id, std::vector<Message>& messages, std::mutex& mtx, std::condition_variable& cv) {
    double value = static_cast<double>(id * 10000);
    bool isLast = false;

    while (value >= 1.0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(id * 100));

        std::unique_lock<std::mutex> lock(mtx);
        messages.push_back({ value, id, isLast });
        isLast = false;
        cv.notify_one();
        lock.unlock();

        value /= 10.0;
    }

    // Send the last message
    std::unique_lock<std::mutex> lock(mtx);
    messages.push_back({ 0.0, id, true });
    cv.notify_one();
}

// Implement the consumer function
void consumer(std::vector<Message>& messages, std::mutex& mtx, std::condition_variable& cv, int& finishedCount) {
    while (finishedCount < 2) {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&messages] { return !messages.empty(); });

        Message msg = messages.front();
        messages.erase(messages.begin());

        if (msg.isLast) {
            finishedCount++;
            std::cout << msg.threadId << " finished." << std::endl;
        }
        else {
            std::cout << msg.value << ": " << msg.threadId << " sent." << std::endl;
        }
    }
}

