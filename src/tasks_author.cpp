#include <iostream>
#include <fstream>
#include <filesystem>

#include "tasks_author.h"
#include "obsidian_task.h"
#include "task2md_conversion/task2md_conversion.cpp"

TasksAuthor::TasksAuthor(std::string tasks_folderpath) : mTasks_folderpath(tasks_folderpath)
{}

TasksAuthor::TasksAuthor(const TasksAuthor& tasks_author) : mTasks_folderpath(tasks_author.mTasks_folderpath) 
{}

TasksAuthor::TasksAuthor(TasksAuthor&& tasks_author) : mTasks_folderpath(tasks_author.mTasks_folderpath) 
{
    tasks_author.mTasks_folderpath = nullptr;
}

TasksAuthor::~TasksAuthor() 
{}

void TasksAuthor::create_event(ObsidianTask* task)
{
    std::string filename = create_event_file(task);
    std::string file_content = convert(&task);
    
    write_into_file(filename, file_content);
    write_into_file(filename, calendar_tasks_file_content_body);
}

void TasksAuthor::delete_task(ObsidianTask* task)
{}

std::string TasksAuthor::get_tasks_folderpath()
{
    return mTasks_folderpath;
}

std::string TasksAuthor::create_event_file(ObsidianTask* task) 
{
    std::string event_filename = generate_event_filename(&folderpath, task)
    std::ofstream tasks_file = std::ofstream(get_tasks_folderpath() + event_filename);

    if (!tasks_file) {
        throw std::ios::failure("The task file of this vault was not created");
    }
    tasks_file.close();
}

std::string TasksAuthor::generate_event_filename(const std::string* folderpath, const ObsidianTask* task)
{
    std::string filename = task->start_date + " " + task->title;
    
    return filename;
}

void TasksAuthor::write_into_file(const std::string filename, const std::string* content)
{

}

void TasksAuthor::delete_from_file(const std::string filename, const int line_number)
{

}
