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
    static constexpr int LOG_LINE_LENGTH = 1024;

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
        thread_local std::array<char,LOG_LINE_LENGTH> msgBuf;

        // Format the main message into the buffer
        auto prefixResult = std::format_to_n( msgBuf.begin(), msgBuf.size() - 1, 
                                         "[{}:{}, {}()] ", file, line, func);

        // Format the actual message after the prefix
        auto messageResult = std::format_to_n(prefixResult.out, 
            msgBuf.end() - prefixResult.out - 1, 
                                          fmt, std::forward<Args>(args)...);

        // Null-terminate manually (in case it's not already terminated)
        if (messageResult.out < msgBuf.end()) {
            *messageResult.out = '\0';
        } else {
            msgBuf.back() = '\0'; // Ensure null termination if buffer is full
        }


        // Send log to journald
        if(_runInSystemd)
            sd_journal_print(priority, "%s", msgBuf.data());
        else
            std::cout << msgBuf.data() << std::endl;
    }



protected:
    SysDLogger();

private:
    bool _runInSystemd;
};



