#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>
#include "filesystem"

#include "doctest.h"
#include "tasks_author.h"
#include "obsidian_task.h"

TEST_SUITE("testing Tasks Author being able to write tasks into the tasks file")
{
    TEST_CASE("testing task only with description")
    {
        ObsidianTask *task = ObsidianTask("Dummy Task");
        std::string expected_md_line = "- #task Dummy Task\n";

        std::string vault_path = "/home/tom-schaepsmeier/Documents/Projects/TTExport";
        REQUIRE(std::filesystem::exists(vault_path) == true);

        TasksAuthor tasks_author = TasksAuthor(vault_path);
        tasks_author.write_task(task);

        std::ifstream file(tasks_author.get_tasks_filepath());
        std::string file_line;
        bool line_found = false;
        while (getline(file, file_line)) {
            if (file_line.compare(expected_md_line) == 0) {
                line_found = true;
            }
        }
        
        CHECK(line_found == true);
    }
}