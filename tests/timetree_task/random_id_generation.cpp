#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <ctime>
#include <vector>

#include "doctest.h"
#include "timetree_task.h"

TEST_SUITE("testing the id generation for each TimeTreeTask instance")
{
    TEST_CASE("testing that the id is exactly 6 characters long")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        TimeTreeTask t1 = TimeTreeTask(&task_title, &start_time, &end_time, false);
        CHECK_EQ(t1.id().length(), 6);
    }

    TEST_CASE("testing that each instance has different ids despite their content")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        std::vector<std::string> task_storage = std::vector<std::string>();
        for (int i = 0; i <= 20; i++)
        {
            TimeTreeTask task = TimeTreeTask(&task_title, &start_time, &end_time, false);
            task_storage.push_back(task.id());
        }

        for (int i = 0; i < 20; i++)
        {
            // we check directly on the id, not using the overloaded == operator of the struct
            CHECK_FALSE(task_storage.at(i) == task_storage.at(i+1));
        }
    }

    TEST_CASE("testing the comparison operator '==' for two instances")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        TimeTreeTask t1 = TimeTreeTask(&task_title, &start_time, &end_time, false);
        TimeTreeTask t2 = TimeTreeTask(&task_title, &start_time, &end_time, false);

        CHECK_NOTHROW(t1 == t2);
        CHECK_FALSE(t1 == t2);
    }
}
