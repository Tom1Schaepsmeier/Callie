#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include <filesystem>

#include "common/EventListener.h"
#include "doctest.h"
#include "tasks_author.h"
#include "obsidian_task.h"
#include "task2md_conversion/task2md_conversion.h"

std::string get_task_file_content(std::filesystem::path folderpath, std::string filename) {
    std::ifstream file(folderpath / filename);

    if (!file.is_open()) {
        throw std::ios::failure("Failed to open task file: " + filename);
    }

    std::string file_content;
    std::string line;
    while (getline(file, line)) {
        file_content += line + "\n";
    }

    file.close();
    return file_content;
}

bool does_task_file_exist(std::filesystem::path folderpath, std::string filename) 
{
    return std::filesystem::exists(folderpath / filename);
}

std::string add_calendar_identifier(std::string content)
{
    return content + "TimeTree\n";
}

TEST_SUITE("testing Tasks Author being able to write tasks into the tasks file")
{
    std::string event_path = "/home/tom-schaepsmeier/Documents/Zettelkasten/6 - Tasks Management/Calendar Tasks";
    TasksAuthor tasks_author = TasksAuthor(event_path);
    EventListener event_listener = EventListener(&event_path);
    
    TEST_CASE("test writing a new full day task which is scheduled for one day")
    {
        event_listener.start();
        ObsidianTask t1("Full Day Task Same Day", "2025-02-12");
        tasks_author.create_event(&t1);

        std::string expected_file_content = convert(&t1);
        expected_file_content = add_calendar_identifier(expected_file_content);
        std::string expected_filename = "2025-02-12 Full Day Task Same Day.md";

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), expected_filename));
        CHECK_EQ(get_task_file_content(tasks_author.get_tasks_folderpath(), expected_filename), expected_file_content);
        event_listener.stop();
        std::vector<std::filesystem::path> created_files = event_listener.retrieve_added_files();
        
        for (const auto &filepath : created_files) {
            std::filesystem::remove(filepath);
        }
        
    }

    TEST_CASE("test writing a new full day task which is scheduled for multiple days")
    {
        ObsidianTask t1("Full Day Task multiple days", "2025-02-12", "2025-02-13");
        tasks_author.create_event(&t1);

        std::string expected_file_content = convert(&t1);
        expected_file_content = add_calendar_identifier(expected_file_content);
        std::string expected_filename = "2025-02-12 Full Day Task multiple days.md";

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), expected_filename));
        CHECK_EQ(get_task_file_content(tasks_author.get_tasks_folderpath(), expected_filename), expected_file_content);
    }

    TEST_CASE("test writing a time scheduled task which is only within one day")
    {
        std::string start_time = "14:30";
        std::string end_time = "17:21";
        ObsidianTask t1("Scheduled Time Task Same day", "2025-02-12", &start_time, &end_time);
        tasks_author.create_event(&t1);

        std::string expected_file_content = convert(&t1);
        expected_file_content = add_calendar_identifier(expected_file_content);
        std::string expected_filename  ="2025-02-12 Scheduled Time Task Same day.md"; 

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), expected_filename));
        CHECK_EQ(get_task_file_content(tasks_author.get_tasks_folderpath(), expected_filename), expected_file_content);
    }

    TEST_CASE("test writing a time scheduled task which goes over multiple days")
    {
        std::string start_time = "15:04";
        std::string end_time = "09:49";
        ObsidianTask t1("Scheduled Time Task multiple days", "2025-02-12", "2025-02-13", &start_time, &end_time);
        tasks_author.create_event(&t1);

        std::string expected_file_content = convert(&t1);
        expected_file_content = add_calendar_identifier(expected_file_content);
        std::string expected_filename  ="2025-02-12 Scheduled Time Task multiple days.md"; 

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), expected_filename));
        CHECK_EQ(get_task_file_content(tasks_author.get_tasks_folderpath(), expected_filename), expected_file_content);
    }

    TEST_CASE("test writing two tasks with same name and date")
    {
        ObsidianTask t1("Test Task", "2025-02-12");
        ObsidianTask t2("Test Task", "2025-02-12");
        tasks_author.create_event(&t1);
        tasks_author.create_event(&t2);

        std::string expected_file_content_1 = convert(&t1);
        std::string expected_file_content_2 = convert(&t2);
        expected_file_content_1 = add_calendar_identifier(expected_file_content_1);
        expected_file_content_2 = add_calendar_identifier(expected_file_content_2);
        std::string expected_filename_1 = "2025-02-12 Test Task 1.md"; 
        std::string expected_filename_2 = "2025-02-12 Test Task 2.md";

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), expected_filename_1));
        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), expected_filename_2));
        CHECK_EQ(get_task_file_content(tasks_author.get_tasks_folderpath(), expected_filename_1), expected_file_content_1);
        CHECK_EQ(get_task_file_content(tasks_author.get_tasks_folderpath(), expected_filename_2), expected_file_content_2);
    }

}