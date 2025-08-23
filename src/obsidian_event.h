#pragma once

#include <ctime>
#include <memory>
#include <string>

#include "timetree_task.h"

struct ObsidianEvent {
    std::string* id;
    std::string* name;
    tm* start_time;
    tm* end_time;
    bool is_full_day;
    std::shared_ptr<std::string> content;
    std::string* location;
    std::string* notes;

    ObsidianEvent(const TimeTreeTask* tt_task);

    ObsidianEvent(const std::ifstream*);

    std::shared_ptr<std::string> get_title() const
    {
        std::string title_month = (start_time->tm_mon < 10) ? "0" + std::to_string(start_time->tm_mon) : std::to_string(start_time->tm_mon);
        std::string title_day = (start_time->tm_mday < 10) ? "0" + std::to_string(start_time->tm_mday) : std::to_string(start_time->tm_mday);

        std::shared_ptr<std::string> event_title = std::shared_ptr<std::string>(new std::string);
        *event_title = std::to_string(start_time->tm_year) + "-" + 
        title_month + "-" + 
        title_day + " " + *name;
        return event_title;
    }
};
