#include <iostream>
#include <ctime>
#include <string>
using namespace std;
int main()
{
    // Get the current time in seconds since the Epoch
    std::time_t currentTime = std::time(nullptr);

    // Convert the time to a local time structure
    std::tm *timeInfo = std::localtime(&currentTime);

    // Extract the time components
    string hours = to_string(timeInfo->tm_hour);
    string minutes = to_string(timeInfo->tm_min);
    string seconds = to_string(timeInfo->tm_sec);
    string time_ = hours + ":" + minutes + ":" + seconds;
    // Print the time
    std::cout << "Current time: " << time_ << endl;

    return 0;
}
