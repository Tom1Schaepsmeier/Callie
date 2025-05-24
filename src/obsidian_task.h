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
    std::string title;
    std::string start_date;
    std::string end_date;
    std::string* start_time;
    std::string* end_time;
    bool isFullDay;

    ObsidianTask(std::string task_title, std::string date) : title(task_title),
                                                            start_date(date),
                                                            end_date(date),
                                                            start_time(nullptr),
                                                            end_time(nullptr),
                                                            isFullDay(true)
    {}

    ObsidianTask(std::string task_title, std::string task_start_date, std::string task_end_date) : title(task_title),
                                                                                                start_date(task_start_date),
                                                                                                end_date(task_end_date),
                                                                                                start_time(nullptr),
                                                                                                end_time(nullptr),
                                                                                                isFullDay(true)
    {}

    ObsidianTask(std::string task_title, std::string date, std::string* task_start_time, 
                    std::string* task_end_time) : title(task_title),
                                            start_date(date),
                                            end_date(date),
                                            start_time(task_start_time),
                                            end_time(task_end_time),
                                            isFullDay(false)
    {}

    ObsidianTask(std::string task_title, std::string task_start_date, std::string task_end_date,
                    std::string* task_start_time, std::string* task_end_time) : title(task_title),
                                                                    start_date(task_start_date),
                                                                    end_date(task_end_date),
                                                                    start_time(task_start_time),
                                                                    end_time(task_end_time),
                                                                    isFullDay(false)
    {}
};