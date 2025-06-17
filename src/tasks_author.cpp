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
    std::filesystem::path tasks_folderpath = get_tasks_folderpath();
    int file_count = get_event_count(task);
    std::cout << "Current file count: " << file_count << std::endl;

    std::string event_filename = generate_event_filename(&tasks_folderpath, task, 0);
    if (file_count == 1)
        number_event(event_filename, file_count);

    std::string filename;
    std::string file_content;
    if (file_count == 0) {
        filename = create_event_file(task, 0);
        file_content = convert(task);
    } else {
        filename = create_event_file(task, file_count + 1);
        ObsidianTask numbered_task = *task;
        numbered_task.title += " " + std::to_string(file_count + 1);
        file_content = convert(&numbered_task);
    }


    
    file_content += calendar_tasks_file_content_body + "\n";
    write_into_file(filename, &file_content);
}

void TasksAuthor::delete_event(const ObsidianTask* task)
{}

std::filesystem::path TasksAuthor::get_tasks_folderpath()
{
    return mTasks_folderpath;
}

std::string TasksAuthor::create_event_file(const ObsidianTask* task, int event_file_number) 
{
    std::filesystem::path tasks_folderpath = get_tasks_folderpath();

    std::string event_filename = generate_event_filename(&tasks_folderpath, task, event_file_number);
    std::ofstream tasks_file = std::ofstream(tasks_folderpath / event_filename );

    if (!tasks_file) {
        throw std::ios::failure("The task file " + event_filename + "could not be created");
    }
    tasks_file.close();
    return event_filename;
}

std::string TasksAuthor::generate_event_filename(const std::filesystem::path* folderpath, const ObsidianTask* task, int number)
{
    std::string filename;
    if (number == 0)
        filename = task->start_date + " " + task->title + ".md";
    else
        filename = task->start_date + " " + task->title + " " + std::to_string(number) + ".md";
    
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

int TasksAuthor::get_event_count(const ObsidianTask* task) {
    std::filesystem::path tasks_folderpath = get_tasks_folderpath();
    std::string default_filename = generate_event_filename(&tasks_folderpath, task, 0);
    std::string default_filename_stem = default_filename.erase(default_filename.size() - 3);
    int filecount = 0;
    for (auto const& event_file : std::filesystem::directory_iterator(tasks_folderpath)) {
        if (event_file.path().filename().generic_string().find(default_filename_stem) != std::string::npos) {
            filecount++;
        }
    }
    return filecount;
}

void TasksAuthor::number_event(std::string event_filename, int number) {
    std::filesystem::path tasks_folderpath = get_tasks_folderpath();
    std::string old_event_filepath = tasks_folderpath / event_filename;
    std::string number_to_insert = " " + std::to_string(number);

    size_t extension_pos = old_event_filepath.rfind('.');
    if (extension_pos == std::string::npos) {
        throw std::runtime_error("Invalid filename, no file extension is specified");
    }

    std::string new_event_filepath = old_event_filepath;
    new_event_filepath.insert(extension_pos, number_to_insert);
    std::rename(old_event_filepath.c_str(), new_event_filepath.c_str());

    // add number to metadata
    std::string buf;
    std::ifstream readFile(new_event_filepath);
    getline(readFile, buf, '\0');
    readFile.close();

    size_t title_pos = buf.find("title: ");
    size_t end_of_line_pos = buf.find('\n', title_pos + 1);
    buf.insert(end_of_line_pos, " " + std::to_string(number));

    std::ofstream writeFile(new_event_filepath);
    writeFile << buf;
    writeFile.close();
}