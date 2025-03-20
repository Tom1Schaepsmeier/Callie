#include <iostream>
#include <fstream>
#include <filesystem>
#include "tasks_author.h"

TasksAuthor::TasksAuthor(std::string vault_path) : mVault_path(vault_path)
{
    mTasks_filename = "calendar_tasks.md";
    create_tasks_file();
}

TasksAuthor::TasksAuthor(const TasksAuthor& tasks_author) : mVault_path(tasks_author.mVault_path),
                                                            mTasks_filename(tasks_author.mTasks_filename) {}

TasksAuthor::TasksAuthor(TasksAuthor&& tasks_author) : mVault_path(tasks_author.mVault_path),
                                                       mTasks_filename(tasks_author.mTasks_filename) {
    tasks_author.mVault_path = nullptr;
}

TasksAuthor::~TasksAuthor() {}

const void TasksAuthor::create_tasks_file() {
    std::cout << "Creating the tasks file" << std::endl;
    std::string full_path = mVault_path + "/" + mTasks_filename;
    std::ofstream tasks_file = std::ofstream(full_path);

    if (!std::filesystem::exists(mVault_path)) {
        std::cerr << "Dir failed";
    }

    if (!tasks_file) {
        std::cerr << "Failed" << std::endl;
        return;
    }
    tasks_file.close();
}

const std::string TasksAuthor::get_vault_path() {
    return mVault_path;
}

const void TasksAuthor::write_task(ObsidianTask *obsidian_task) {}

const void TasksAuthor::delete_task(ObsidianTask *obsidian_task) {}