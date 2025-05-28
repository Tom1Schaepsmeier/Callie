#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <fstream>
#include <iostream>
#include <string>

#include "doctest.h"
#include "obsidian_task.h"
#include "task2md_conversion/task2md_conversion.h"

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

TEST_SUITE("test a task with scheduled time is converted correctly") {

    TEST_CASE("test valid scheduled times at the same day") {
        std::string expected_task_file_content = get_task_file_content("/home/tom-schaepsmeier/Documents/Projects/TTExport/tests/task2md_conversion/expected_scheduled_time_same_date_task.txt");
        std::string start_time = "14:12";
        std::string end_time = "20:53";
        ObsidianTask t1("Scheduled Time Task", "2025-02-12", &start_time, &end_time);

        std::string actual_task_file_content = convert(&t1);
        CHECK_EQ(actual_task_file_content, expected_task_file_content);

    }

    TEST_CASE("test valid scheduled times over midnight") {
        std::string expected_task_file_content = get_task_file_content("/home/tom-schaepsmeier/Documents/Projects/TTExport/tests/task2md_conversion/expected_scheduled_time_different_date_task.txt");
        std::string start_time = "21:52";
        std::string end_time = "04:22";
        ObsidianTask t1("Scheduled Time Task", "2025-02-12", "2025-02-13", &start_time, &end_time);

        std::string actual_task_file_content = convert(&t1);
        CHECK_EQ(actual_task_file_content, expected_task_file_content);
    }
}