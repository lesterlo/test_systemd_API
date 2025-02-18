#include <systemd/sd-journal.h>
#include <systemd/sd-daemon.h>
#include <unistd.h>
#include <string>
#include <iostream>

bool is_running_with_systemd() {
    return getenv("INVOCATION_ID") != nullptr;
}

void print_message(int counter)
{
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
    
}

int main() {
    int counter = 0;

    if (is_running_with_systemd()) {
        sd_notify(0, "READY=1");
    }

    while (true) {
        
        print_message(counter);
        

        if (is_running_with_systemd()) 
        {
            sd_notify(0, "WATCHDOG=1");

            sd_journal_send("MESSAGE=%s", ("[systemd] loop complete"+std::to_string(counter)).c_str(), "PRIORITY=%i", LOG_INFO, NULL);
        }
        else
        {
            std::cout << "[Raw] loop #" << counter << ": completed" << std::endl;
        }

        counter++;
        sleep(10);  // Avoid overwhelming the system logs
    }

    return 0;
}
