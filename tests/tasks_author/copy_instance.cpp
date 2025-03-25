#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <string>

#include "doctest.h"
#include "tasks_author.h"

TEST_SUITE("testing the copy constructor") 
{
    TEST_CASE("successful copying the instance")
    {
        std::string vault_path = "/home/tom-schaepsmeier/Documents/Projects/TTExport";
        TasksAuthor t1 = TasksAuthor(vault_path);

        TasksAuthor t2 = TasksAuthor(t1);

        CHECK_EQ(t1.get_vault_path(), t2.get_vault_path());
        CHECK_EQ(t1.get_tasks_filepath(), t2.get_tasks_filepath());
    }
}