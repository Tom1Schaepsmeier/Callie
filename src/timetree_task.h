#pragma once
#include <ctime>
#include <string>

struct TimeTreeTask {
    std::string* title;
    tm* start_time;
    tm* end_time;
    bool is_full_day;
    std::string* location;
    std::string* notes;

    TimeTreeTask(std::string* task_title, tm* task_start_time, 
                 tm* task_end_time, bool is_task_full_day, 
                 std::string* task_location=nullptr, std::string* task_notes=nullptr) : title(task_title),
                                                    start_time(task_start_time),
                                                    end_time(task_end_time),
                                                    is_full_day(is_task_full_day),
                                                    location(task_location),
                                                    notes(task_notes)
    {
        if (task_end_time < task_start_time)
            throw;
    }
};