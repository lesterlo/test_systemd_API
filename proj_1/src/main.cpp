#include <systemd/sd-journal.h>
#include <unistd.h>
#include <string>
#include <iostream>

int main() {
    int counter = 0;

    while (true) {
        std::string message;

        message = "Debug message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_DEBUG, NULL);

        message = "Info message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_INFO, NULL);

        message = "Notice message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_NOTICE, NULL);

        message = "Warning message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_WARNING, NULL);

        message = "Error message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_ERR, NULL);

        message = "Critical message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_CRIT, NULL);

        message = "Alert message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_ALERT, NULL);

        message = "Emergency message #" + std::to_string(counter);
        sd_journal_send("MESSAGE=%s", message.c_str(), "PRIORITY=%i", LOG_EMERG, NULL);

        counter++;
        sleep(10);  // Avoid overwhelming the system logs
    }

    return 0;
}
