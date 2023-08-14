#include "assignment.h"

int main() {
    std::vector<Message> messages;
    std::mutex mtx;
    std::condition_variable cv;
    int finishedCount = 0;

    // Create and start the consumer thread
    std::thread consumerThread(consumer, std::ref(messages), std::ref(mtx), std::ref(cv), std::ref(finishedCount));

    // Create and start two producer threads
    std::thread producerThread1(producer, 1, std::ref(messages), std::ref(mtx), std::ref(cv));
    std::thread producerThread2(producer, 2, std::ref(messages), std::ref(mtx), std::ref(cv));

    // Wait for all threads to finish
    producerThread1.join();
    producerThread2.join();
    consumerThread.join();

    return 0;
}
