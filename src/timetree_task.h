#pragma once
#include <ctime>
#include <iostream>
#include <memory>
#include <string>

struct TimeTreeTask {
    std::string* title;
    tm* start_time;
    tm* end_time;
    bool is_full_day;
    std::string* location;
    std::shared_ptr<std::string> notes;

    TimeTreeTask(std::string* task_title, tm* task_start_time, 
                 tm* task_end_time, bool is_task_full_day, 
                 std::string* task_location=nullptr, std::string* task_notes=nullptr);

    friend std::ostream& operator<<(std::ostream& os, const TimeTreeTask& tt_task);

    bool operator==(const TimeTreeTask& other);

    std::string id() const;
                
    private:
        std::string id_;
        void generate_id();
};