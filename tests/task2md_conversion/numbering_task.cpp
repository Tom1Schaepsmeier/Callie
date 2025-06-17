#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include "doctest.h"
#include "obsidian_task.h"
#include "task2md_conversion/task2md_conversion.h"

TEST_SUITE("Testing numbering correctly an existing ObsidianTask") {
    TEST_CASE("adding a positive number") {
        ObsidianTask task = ObsidianTask("To be numbered task", "2025-02-12");
        number_task(&task, 1);
        CHECK_EQ(task.title, "To be numbered task 1");
    }

    TEST_CASE("adding a zero as a number") {
        ObsidianTask task = ObsidianTask("To be numbered task", "2025-02-12");
        number_task(&task, 0);
        CHECK_EQ(task.title, "To be numbered task");
    }

    TEST_CASE("adding a negative number") {
        ObsidianTask task = ObsidianTask("To be numbered task", "2025-02-12");
        number_task(&task, -1);
        CHECK_EQ(task.title, "To be numbered task");
    }
}