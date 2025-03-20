#include <iostream>
#include <fstream>
#include <filesystem>
#include "tasks_author.h"
#include "markdown_writer.h"

TasksAuthor::TasksAuthor(std::string vault_path) : mVault_path(vault_path)
{
    std::string tasks_filename = "calendar_tasks.md";
    std::string tasks_filepath = create_tasks_file(tasks_filename);
    mMarkdown_writer = MarkdownWriter(tasks_filepath);
}

TasksAuthor::TasksAuthor(const TasksAuthor& tasks_author) : mVault_path(tasks_author.mVault_path) {}

TasksAuthor::TasksAuthor(TasksAuthor&& tasks_author) : mVault_path(tasks_author.mVault_path) {
    tasks_author.mVault_path = nullptr;
}

TasksAuthor::~TasksAuthor() {}

const std::string TasksAuthor::create_tasks_file(const std::string filename) {
    std::cout << "Creating the tasks file" << std::endl;
    std::string full_path = mVault_path + "/" + filename;
    std::ofstream tasks_file = std::ofstream(full_path);

    if (!tasks_file) {
        std::cerr << "Failed" << std::endl;
        return;
    }
    tasks_file.close();

    return full_path;
}

const std::string TasksAuthor::get_vault_path() {
    return mVault_path;
}

const void TasksAuthor::write_task(ObsidianTask *obsidian_task) {}

const void TasksAuthor::delete_task(ObsidianTask *obsidian_task) {}