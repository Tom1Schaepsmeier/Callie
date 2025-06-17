#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <filesystem>
#include <iostream>

#include "doctest.h"
#include "tasks_author.h"
#include "task2md_conversion/task2md_conversion.h"
#include "common/EventListener.h"

std::string get_task_file_content(std::string filename) {
    std::ifstream file(filename);

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


TEST_SUITE("updating an existing event file by specifying a new ObsidianTask instance") {
    std::string event_directory = "/home/tom-schaepsmeier/Documents/Zettelkasten/6 - Tasks Management/Calendar Tasks";
    std::filesystem::path event_path{event_directory};
        
    TEST_CASE("event only has metadata") {
        EventListener event_listener = EventListener(&event_directory);
        event_listener.start();

        TasksAuthor tasks_author = TasksAuthor(event_directory);
        ObsidianTask t1 = ObsidianTask("Only Metadata task", "2025-02-12");
        ObsidianTask t2 = ObsidianTask("New only Metadata task", "2025-02-13");
        std::string expected_initial_filename = "2025-02-12 Only Metadata task.md";
        std::string expected_file_content = convert(&t2);

        tasks_author.create_event(&t1);
        update_event(&event_path, &expected_initial_filename, &t2);
        
        CHECK(std::filesystem::exists(event_path / "2025-02-13 New only Metadata task"));
        CHECK(!(std::filesystem::exists(event_path / expected_initial_filename)));
        CHECK_EQ(get_task_file_content(event_path / "2025-02-13 New only Metadata task"), expected_file_content);

        event_listener.stop();
        for (const auto &filepath : event_listener.retrieve_added_files()) {
            std::filesystem::remove(filepath);
        }
    }

    TEST_CASE("old event contains individual text") {
        /*
        Requirement will probably change later
        */


        EventListener event_listener = EventListener(&event_directory);
        event_listener.start();

        TasksAuthor tasks_author = TasksAuthor(event_directory);
        std::string custom_text = "This is a custom text";
        ObsidianTask t1 = ObsidianTask("Task with custom text", "2025-02-12");
        ObsidianTask t2 = ObsidianTask("New task with custom text", "2025-02-12");
        std::string expected_initial_filename = "2025-02-12 Task with custom text";
        std::string expected_file_content = convert(&t2); // TODO: add custom text to expected content

        tasks_author.create_event(&t1);
        update_event(&event_path, &expected_initial_filename, &t2);

        CHECK(std::filesystem::exists(event_path / "2025-02-12 New task with custom text"));
        CHECK(!std::filesystem::exists(event_path / expected_initial_filename));
        CHECK_EQ(get_task_file_content(event_path / "2025-02-13 New task with custom text"), expected_file_content);

        event_listener.stop();
        for (const auto &filepath : event_listener.retrieve_added_files()) {
            std::filesystem::remove(filepath);
        }
    }

    TEST_CASE("new event name already exists") {
        EventListener event_listener = EventListener(&event_directory);
        event_listener
    }
}