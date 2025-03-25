#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <string>
#include <filesystem>
#include "doctest.h"
#include "tasks_author.h"

TEST_SUITE("testing the default constructor") {
    
    TEST_CASE("tasks file is created successfully") {
        std::string vault_path = "/home/tom-schaepsmeier/Documents/Projects/TTExport";
        REQUIRE(std::filesystem::exists(vault_path) == true);
    
        TasksAuthor tasks_author = TasksAuthor(vault_path);
        
        REQUIRE(tasks_author.get_vault_path() == vault_path);
        CHECK(std::filesystem::exists(tasks_author.get_tasks_filepath()) == true);
    }

    TEST_CASE("tasks file is not created due to an error") {
        std::string vault_path = "/home/not-existing-user";
        REQUIRE_FALSE(std::filesystem::exists(vault_path));

        CHECK_THROWS(TasksAuthor(vault_path));

    }
}
