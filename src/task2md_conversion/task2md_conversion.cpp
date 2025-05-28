#include <iostream>
#include <string>

#include "obsidian_task.h"
#include "task2md_conversion/task2md_conversion.h"

std::string convertFullDayTask(const ObsidianTask* task) {
    std::string date;
    std::string all_day_entry = "allDay: true\n";
    
    date += all_day_entry;
    if (task->end_date > task->start_date) {
        date += "startDate: " + task->start_date + "\n";
        date += "endDate: " + task->end_date + "\n";
    } else {
        date += "date: " + task->start_date + "\n";
    }
    
    return date;
}

std::string convertScheduledTimeTask(const ObsidianTask* task) {
    std::string date_and_time;
    std::string all_day_entry = "allDay: false\n";

    date_and_time += all_day_entry;
    date_and_time += "startTime: " + *(task->start_time) + "\n";
    date_and_time += "endTime: " + *(task->end_time) + "\n";


    if (task->end_date > task->start_date) {
        date_and_time += "startDate: " + task->start_date + "\n";
        date_and_time += "endDate: " + task->end_date + "\n"; 
    } else {
        date_and_time += "date: " + task->start_date + "\n";
    }

    return date_and_time;
}

std::string convertTimeAndDateInformation(const ObsidianTask* task) {
    std::string time_and_date_information;
    
    if (task->isFullDay)
        time_and_date_information = convertFullDayTask(task);
    else
        time_and_date_information = convertScheduledTimeTask(task);
    
    return time_and_date_information;
}

std::string convert(const ObsidianTask* task){
    std::string task_file_content;

    task_file_content += "---\n";
    task_file_content += "title: " + task->title + "\n";
    task_file_content += convertTimeAndDateInformation(task);
    task_file_content += "completed: null\n";
    task_file_content += "type: single\n";
    task_file_content += "---\n";

    return task_file_content;
}