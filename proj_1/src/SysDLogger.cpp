#include "SysDLogger.h"

SysDLogger::~SysDLogger() {}

SysDLogger::SysDLogger()
{
    _runInSystemd = (getenv("INVOCATION_ID") != nullptr)? true : false;
}

void SysDLogger::sysReady()
{
    if (_runInSystemd) {
        sd_notify(0, "READY=1");
    }
}

void SysDLogger::feedWatchdog()
{
    if (_runInSystemd) {
        sd_notify(0, "WATCHDOG=1");
    }
}
