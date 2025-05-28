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

TEST_SUITE("test full day tasks") {

    /*
    When our task contains a valid date then we need to create a obsidian fullcalendar task string
    which contains the header with correct format
    */
    TEST_CASE("test valid date on same day") {
        std::string expected_task_file_content = get_task_file_content("/home/tom-schaepsmeier/Documents/Projects/TTExport/tests/task2md_conversion/expected_full_day_same_date_task.txt");
        ObsidianTask t1("FullDay task", "2025-02-12");
        
        std::string actual_task_file_content = convert(&t1);

        CHECK_EQ(actual_task_file_content, expected_task_file_content);
    }

    TEST_CASE("test valid dates on different days") {
        std::string expected_task_file_content = get_task_file_content("/home/tom-schaepsmeier/Documents/Projects/TTExport/tests/task2md_conversion/expected_full_day_different_date.txt");
        ObsidianTask t1("FullDay task", "2025-02-12", "2025-02-13");

        std::string actual_task_file_content = convert(&t1);

        CHECK_EQ(actual_task_file_content, expected_task_file_content);
        
    }
}
