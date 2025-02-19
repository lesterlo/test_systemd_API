#include <unistd.h>
#include <string>
#include <iostream>
#include "SysDLogger.h"

bool is_running_with_systemd() {
    return getenv("INVOCATION_ID") != nullptr;
}

// void print_message(int counter)
// {
//     std::array<char, 64> buffer;
//     auto result = std::format_to_n(buffer.begin(), buffer.size() - 1, "Debug message #{}", counter);
//     *result.out = '\0';  // Null-terminate safely

//     sd_journal_send("MESSAGE=%s", buffer.data(), "PRIORITY=%i", LOG_DEBUG, NULL);
// }

void print_message(int counter)
{
    LOGGING(LOG_DEBUG,"Debug message #{}", counter);
    LOGGING(LOG_INFO,"Info message #{}",counter);
    LOGGING(LOG_NOTICE,"Notice message #{}",counter);
    LOGGING(LOG_WARNING,"Warning message #{}",counter);
    LOGGING(LOG_ERR, "Error message #{}",counter);
    LOGGING(LOG_CRIT,"Critical message #{}",counter);
    LOGGING(LOG_ALERT,"Alert message #{}",counter);
    LOGGING(LOG_EMERG,"Emergency message #{}",counter);
}

int main() {
    int counter = 0;

    SysDLogger::getInstance().sysReady();

    while (true) {
        
        SysDLogger::getInstance().feedWatchdog();
        
        print_message(counter);
        

        counter++;
        sleep(10);  // Avoid overwhelming the system logs
    }

    return 0;
}
