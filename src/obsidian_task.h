#pragma once
#include <ctime>
#include <string>

struct ObsidianTask {
    std::string title;
    tm* start_time;
    tm* end_time;
    bool isFullDay;

    ObsidianTask(std::string task_title, tm* time) : title(task_title),
                                                    start_time(time)
    {
        
    }
    
    ObsidianTask(std::string task_title, tm* task_start_time, tm* task_end_time) : title(task_title),
                                                                                   start_time(task_start_time),
                                                                                   end_time(task_end_time)
    {}
};