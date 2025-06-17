#ifndef TASKS_AUTHOR_H
#define TASKS_AUTHOR_H

#include <string>
#include <filesystem>
#include <fstream>

#include "obsidian_task.h"

class TasksAuthor {
    std::filesystem::path mTasks_folderpath;
    std::string calendar_tasks_file_content_body = "TimeTree";

    /*
    Creates the markdown file we are allowed to write in if it does not exist already

    @param filename (string) - specifies how the file should be named
    @param number (integer) - the number which should the file contain
    @return the absolute path to that file
    */
    std::string create_event_file(const ObsidianTask* task, int number);

    /*
    Generates the filename of the new Task by parsing the title + date and scanning the folder for similar names

    @param folderpath (std::string*) - the folder the file will be created in
    @param task (ObsidianTask*) - the event we parse to generate the filename
    @param number (int) - adds a number to the filename (if not zero) to differentiate each task from eachother
    @return the filename
    */
    std::string generate_event_filename(const std::filesystem::path* folderpath, const ObsidianTask* task, int number);

    /*
    Writes a line at the end of the markdown file

    @param content (std::string) - holds the characters that will be written into the file
    */
    void write_into_file(const std::string filename, const std::string* content);

    /*
    TODO:
    */
    void delete_from_file(const std::string filename, const int line_number);

    /*
    Parses the event directory and finds the number of events with the same date and name

    @param task (const ObsidianTask*) - 
    @return number of equal events
    */
    int get_event_count(const ObsidianTask* task);

    /*
    Adds a number to the event filename and its metadata task name

    @param event_filename (std::string) - file in the tasks folder which shall be numbered
    */
    void number_event(std::string event_filename, int number);

    public:
        /*
        Default constructor

        @param tasks_folder_path (std::string) - specifies the path to the tasks folder
        */
        TasksAuthor(std::string tasks_folder_path);
        
        /*
        Copy Constructor

        @param tasks_author (TasksAuthor&) - 
        */
        TasksAuthor(const TasksAuthor& tasks_author);
        
        /*
        Move Constructor

        @param tasks_author (TasksAuthor&&) - 
        */
        TasksAuthor(TasksAuthor&& tasks_author);

        /*
        Destructor
        */
        ~TasksAuthor();

        /*
        Returns the full path of the tasks filename
        */
        std::filesystem::path get_tasks_folderpath();

        /*
        Creates a task file and writes the event into the obsidian vault

        @param obsidian_task (ObsidianTask*) - specifies all task related values to be written into the vault
        */
        void create_event(const ObsidianTask* obsidian_task);

        /*
        Deletes a task from the obsidian vault

        @param obsidian_task (ObsidianTask*) - specifies the task to be deleted
        */
        void delete_event(const ObsidianTask* obsidian_task);
};

#endif