#include <ctime>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <stdlib.h>
#include <string.h>

#include "timetree_task.h"

TimeTreeTask::TimeTreeTask(std::string* task_title, tm* task_start_time, 
                 tm* task_end_time, bool is_task_full_day, 
                 std::string* task_location, std::string* task_notes) : title(task_title),
                                                    start_time(task_start_time),
                                                    end_time(task_end_time),
                                                    is_full_day(is_task_full_day),
                                                    location(task_location),
                                                    notes(task_notes)
{
    if (std::mktime(task_end_time) < std::mktime(task_start_time))
        throw std::invalid_argument("The End Time of the task cannot be earlier than its Start Time");

    generate_id();
}

TimeTreeTask::TimeTreeTask(std::string* task_id, std::string* task_title, tm* task_start_time,
                tm* task_end_time, bool is_task_full_day,
                std::string* task_location, std::string* task_notes) : title(task_title),
                                                                       start_time(task_start_time),
                                                                       end_time(task_end_time),
                                                                       is_full_day(is_task_full_day),
                                                                       location(task_location),
                                                                       notes(task_notes),
                                                                       id_(*task_id)
{
    if (std::mktime(task_end_time) < std::mktime(task_start_time))
        throw std::invalid_argument("The End Time of the task cannot be earlier than its Start Time");

    verify_id();
}                                                                       

std::ostream& TimeTreeTask::operator<<(std::ostream& os) const
{
    os << id();
    return os;
}

bool TimeTreeTask::operator==(const TimeTreeTask& other) const
{
    return (this->id().compare(other.id()) == 0);
}


std::string TimeTreeTask::id() const
{
    return this->id_;
}

void TimeTreeTask::generate_id()
{
    id_ = "";
    for (int i=0;i<=5;i++) // we want to create an id which is 6 characters long
    {
        char buf [2];
        int num = rand() % 16;
        sprintf(buf, "%x", num);
        id_ += buf;
    }
}

void TimeTreeTask::verify_id() const
{
    if (id_.length() != 6)
        throw std::invalid_argument("The given value for the id is invalid, it must have exactly 6 characters.");

    std::string allowed_characters = "0123456789abcdef";
    for (auto &character : id_)
    {
        if (allowed_characters.find(character) == std::string::npos)
            throw std::invalid_argument("The given id contains at least one character that is not within the hexadecimal range");
    }
}
