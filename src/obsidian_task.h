#pragma once
#include <string>

enum Priority {
    LOWEST,
    LOW,
    NORMAL,
    MEDIUM,
    HIGH,
    HIGHEST
};

struct ObsidianTask {
    std::string description;
    Priority *priority;
    time_t due;
    time_t scheduled;
    time_t start;
    std::string file;
};