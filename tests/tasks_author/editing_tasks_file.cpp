#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include "filesystem"

#include "doctest.h"
#include "tasks_author.h"
#include "obsidian_task.h"

bool does_task_file_exist(std::string folderpath, ObsidianTask* t1) 
{
    
    return true;
}

TEST_SUITE("testing Tasks Author being able to write tasks into the tasks file")
{
    TasksAuthor tasks_author = TasksAuthor("/home/tom-schaepsmeier/Documents/Zettelkasten/6 - Tasks Management/Calendar Tasks");
    
    TEST_CASE("test writing a new full day task which is scheduled for one day")
    {
        ObsidianTask t1("Full Day Task Same Day", "2025-02-12");

        tasks_author.create_event(&t1);

        CHECK(does_task_file_exist(tasks_author.get_tasks_filepath(), &t1));

    }

    TEST_CASE("test writing a new full day task which is scheduled for multiple days")
    {
        ObsidianTask t1("Full Day Task multiple days", "2025-02-12", "2025-02-13");
        
        tasks_author.create_event(&t1);

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), &t1))
    }

    TEST_CASE("test writing a time scheduled task which is only within one day")
    {
        std::string start_time = "14:30";
        std::string end_time = "17:21";
        ObsidianTask t1("Scheduled Time Task Same day", "2025-02-12", &start_time, &end_time);

        tasks_author.create_event(&t1);

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), &t1));
    }

    TEST_CASE("test writing a time scheduled task which goes over multiple days")
    {
        std::string start_time = "15:04";
        std::string end_time = "09:49";
        ObsidianTask t1("Scheduled Time Task multiple days");

        tasks_author.create_event(&t1);

        CHECK(does_task_file_exist(tasks_author.get_tasks_folderpath(), &t1));
    }

    TEST_CASE("test writing two tasks with same name and date")
    {
        ObsidianTask t1("Test Task", "2025-02-12");
        ObsidianTask t2("Test Task", "2025-02-12");

        tasks_author.create_event(&t1);
        tasks_author.create_event(&t2);

        CHECK()
    }

}