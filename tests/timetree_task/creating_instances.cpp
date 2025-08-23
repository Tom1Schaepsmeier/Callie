#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <ctime>

#include "doctest.h"
#include "timetree_task.h"

TEST_SUITE("testing the correct creation of TimeTreeTask instances")
{
    TEST_CASE("testing correct instantiation with all required parameters for not a full day task")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        
        REQUIRE_NOTHROW(TimeTreeTask t1 = TimeTreeTask(&task_title, &start_time, &end_time, false));
        TimeTreeTask t2 = TimeTreeTask(&task_title, &start_time, &end_time, false);
        CHECK_EQ(*t2.title, task_title);
        CHECK_EQ(std::mktime(t2.start_time), std::mktime(&start_time));
        CHECK_EQ(std::mktime(t2.end_time), std::mktime(&end_time));
        CHECK_EQ(t2.is_full_day, false);
        CHECK_EQ(t2.location, nullptr);
        CHECK_EQ(t2.notes, nullptr);
    }

    TEST_CASE("testing correct instantiation with all required parameter for full day task")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        
        REQUIRE_NOTHROW(TimeTreeTask t1 = TimeTreeTask(&task_title, &start_time, &end_time, true));
        TimeTreeTask t2 = TimeTreeTask(&task_title, &start_time, &end_time, true);
        CHECK_EQ(*t2.title, task_title);
        CHECK_EQ(std::mktime(t2.start_time), std::mktime(&start_time));
        CHECK_EQ(std::mktime(t2.end_time), std::mktime(&end_time));
        CHECK_EQ(t2.is_full_day, true);
        CHECK_EQ(t2.location, nullptr);
        CHECK_EQ(t2.notes, nullptr);
    }

    TEST_CASE("testing correct instantiation when all available parameters are given")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        std::string task_location = "At home";
        std::string task_notes = "My own notes";

        REQUIRE_NOTHROW(TimeTreeTask t1 = TimeTreeTask(&task_title, &start_time, &end_time, true, &task_location, &task_notes));
        TimeTreeTask t2 = TimeTreeTask(&task_title, &start_time, &end_time, true, &task_location, &task_notes);
        CHECK_EQ(*t2.title, task_title);
        CHECK_EQ(std::mktime(t2.start_time), std::mktime(&start_time));
        CHECK_EQ(std::mktime(t2.end_time), std::mktime(&end_time));
        CHECK_EQ(t2.is_full_day, true);
        CHECK_EQ(*t2.location, task_location);
        CHECK_EQ(*t2.notes, task_notes);
    }

    TEST_CASE("testing exception being thrown when end time is earlier than start time")
    {
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        CHECK_THROWS(TimeTreeTask(&task_title, &start_time, &end_time, false));
    }

    TEST_CASE("testing id being correctly stored as given, when part of the constructor")
    {
        std::string task_id = "7a3fdb";
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        TimeTreeTask t1 = TimeTreeTask(&task_id, &task_title, &start_time, &end_time, false);
        CHECK_EQ(t1.id(), task_id);
    }

    TEST_CASE("testing error being thrown when length of id is not 6")
    {
        srand(time(NULL));
        std::string task_id = "";
        int id_length;
        do {
            id_length = (rand() % 20) + 1;
        } while (id_length == 6);

        for (int i=0;i<=id_length-1;i++) // we want to create an id which is 6 characters long
        {
            char buf [2];
            int num = rand() % 16;
            sprintf(buf, "%x", num);
            task_id += buf;
        }

        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        CHECK_THROWS(TimeTreeTask(&task_id, &task_title, &start_time, &end_time, false));
    }

    TEST_CASE("testing error being thrown when id contains non hexadecimal characters (0-9a-f)")
    {
        std::string task_id = "4fd91a";
        std::string task_title = "Test Task";
        tm start_time = { .tm_sec=0, .tm_min=36, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};
        tm end_time = { .tm_sec=0, .tm_min=37, .tm_hour=4, .tm_mday=12, .tm_mon=2, .tm_year=2025};

        std::string non_id_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ.+# ;,-_/&%$§?=";
        for (int i=0;i<(int)task_id.length();i++)
        {
            std::string invalid_id = task_id;
            int replacing_character = rand() % non_id_characters.length();
            invalid_id[i] = replacing_character;
            CHECK_THROWS(TimeTreeTask(&invalid_id, &task_title, &start_time, &end_time, false)); 
        }
    }
}