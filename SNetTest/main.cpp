#include "main.h"

#include <ctime>
#include <iomanip>

std::string getFormattedTime()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm *timeInfo = std::gmtime(&currentTime);

    std::ostringstream oss;
    oss << std::put_time(timeInfo, "%a, %d %b %Y %H:%M:%S GMT");
    return oss.str();
}

using namespace snet;

int main() {
    
}