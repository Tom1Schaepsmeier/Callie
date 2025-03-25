#include <iostream>
#include <fstream>
#include <filesystem>

#include "tasks_author.h"
#include "obsidian_task.h"

TasksAuthor::TasksAuthor(std::string vault_path) : mVault_path(vault_path),
                                                   mTasks_filename("calendar_tasks.md")
{
    create_tasks_file();
}

TasksAuthor::TasksAuthor(const TasksAuthor& tasks_author) : mVault_path(tasks_author.mVault_path),
                                                            mTasks_filename(tasks_author.mTasks_filename) 
{}

TasksAuthor::TasksAuthor(TasksAuthor&& tasks_author) : mVault_path(tasks_author.mVault_path),
                                                       mTasks_filename(tasks_author.mTasks_filename) 
{
    tasks_author.mVault_path = nullptr;
    tasks_author.mTasks_filename = nullptr;
}

TasksAuthor::~TasksAuthor() 
{}

void TasksAuthor::create_tasks_file() 
{
    std::string filepath = get_tasks_filepath();
    std::ofstream tasks_file = std::ofstream(filepath);

    if (!tasks_file) {
        throw std::ios::failure("The task file of this vault was not created");
    }
    tasks_file.close();
}

const std::string TasksAuthor::get_vault_path() 
{
    return mVault_path;
}

std::string TasksAuthor::get_tasks_filepath() 
{
    return get_vault_path() + "/" + mTasks_filename;
}

void TasksAuthor::write_task(const ObsidianTask *obsidian_task) 
{}

void TasksAuthor::delete_task(ObsidianTask *obsidian_task) 
{}