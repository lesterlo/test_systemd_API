#pragma once
#include <systemd/sd-daemon.h>
#include <systemd/sd-journal.h>
#include <string>
#include <format>
#include <iostream>

// Macro to simplify logging
#define LOGGING(level, fmt, ...) SysDLogger::getInstance().log(level, __FILE_NAME__, __LINE__, __FUNCTION__, fmt, ##__VA_ARGS__)


class SysDLogger
{
public:

    static SysDLogger& getInstance()
    {
        static SysDLogger instance;
        return instance;
    }

    ~SysDLogger();
    // Delete copy and move constructors to enforce Singleton pattern
    SysDLogger(const SysDLogger&) = delete;
    SysDLogger& operator=(const SysDLogger&) = delete;
    SysDLogger(SysDLogger&&) = delete;
    SysDLogger& operator=(SysDLogger&&) = delete;


    // Methods
    void sysReady();
    void feedWatchdog();


    //Template function
    template <typename... Args>
    void log(int priority, const char* file, int line, const char* func, std::format_string<Args...> fmt, Args&&... args)
    {
        std::string message = std::format(fmt, std::forward<Args>(args)...);
        std::string finalMessage = std::format("[{}:{}, {}()] {}", file, line, func, message);

        // Send log to journald
        if(_runInSystemd)
            sd_journal_print(priority, "%s", finalMessage.c_str());
        else
            std::cout << finalMessage << std::endl;
    }



protected:
    SysDLogger();

private:
    bool _runInSystemd;
};



