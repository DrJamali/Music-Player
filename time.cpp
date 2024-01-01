#include <iostream>
#include <chrono>
#include <ctime>

int main() {
    // Get the current time point
    auto currentTimePoint = std::chrono::system_clock::now();

    // Convert the time point to a time_t object
    std::time_t currentTime = std::chrono::system_clock::to_time_t(currentTimePoint);

    // Convert the time_t object to a tm structure
    struct std::tm* timeInfo = std::localtime(&currentTime);

    // Print the current time
    std::cout << "Current time: " << std::asctime(timeInfo);

    return 0;
}
