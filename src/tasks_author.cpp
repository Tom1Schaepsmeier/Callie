#include <iostream>
#include <fstream>
#include <filesystem>

#include "tasks_author.h"
#include "obsidian_task.h"
#include "task2md_conversion/task2md_conversion.h"

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

void TasksAuthor::create_event(const ObsidianTask* task)
{
    std::string filename = create_event_file(task);
    std::string file_content = convert(task);
    file_content += calendar_tasks_file_content_body + "\n";
    
    write_into_file(filename, &file_content);
}

void TasksAuthor::delete_event(const ObsidianTask* task)
{}

std::filesystem::path TasksAuthor::get_tasks_folderpath()
{
    return mTasks_folderpath;
}

std::string TasksAuthor::create_event_file(const ObsidianTask* task) 
{
    std::filesystem::path tasks_folderpath = get_tasks_folderpath();
    std::string event_filename = generate_event_filename(&tasks_folderpath, task);

    //if (task_file_exists(&event_filename))

    std::ofstream tasks_file = std::ofstream(tasks_folderpath / event_filename );

    if (!tasks_file) {
        throw std::ios::failure("The task file " + event_filename + "could not be created");
    }
    tasks_file.close();
    return event_filename;
}

std::string TasksAuthor::generate_event_filename(const std::filesystem::path* folderpath, const ObsidianTask* task)
{
    std::string filename = task->start_date + " " + task->title + ".md";
    
    return filename;
}

void TasksAuthor::write_into_file(const std::string filename, const std::string* content)
{
    std::ofstream out_file(get_tasks_folderpath() / filename);
    out_file << *content;
    out_file.close();
}

void TasksAuthor::delete_from_file(const std::string filename, const int line_number)
{

}
