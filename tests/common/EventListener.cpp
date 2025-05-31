#pragma once

#include <iostream>
#include <filesystem>
#include <thread>
#include <unistd.h>
#include <unordered_set>
#include "EventListener.h"

/*
Default constructor
*/
EventListener::EventListener(std::string* event_directory) : is_observing(false)
{
    mEvent_directory = std::filesystem::path(*event_directory);
    if (!std::filesystem::exists(mEvent_directory))
        throw std::ios::failure("The given event directory: " + *event_directory + "does not exist");
}

/*
Copy Constructor
*/
EventListener::EventListener(const EventListener& event_observer) : mEvent_directory(event_observer.mEvent_directory),
                                                                    mAdded_files(event_observer.mAdded_files),
                                                                    is_observing(event_observer.is_observing)
{}

/*
Move Constructor
*/
EventListener::EventListener(EventListener&& event_observer) : mEvent_directory(event_observer.mEvent_directory),
                                                               mAdded_files(event_observer.mAdded_files),
                                                               is_observing(event_observer.is_observing)
{
    event_observer.mAdded_files.clear();
}

/*
Destructor
*/
EventListener::~EventListener() 
{}

/*
Starts observing the directory for file changes
*/
void EventListener::start()
{
    is_observing = true;
    std::thread observer_thread(observe_event_directory);
    observer_thread.detach();
}

/*
Stops observing the directory for file changes
*/
void EventListener::stop()
{
    is_observing = false;
    sleep(1);
}

/*

*/
std::vector<std::filesystem::path> EventListener::retrieve_added_files()
{
    return mAdded_files;
}

/*
Observes the directory in a loop and stores added files 
*/
void EventListener::observe_event_directory()
{
    std::unordered_set<std::filesystem::path> last_iteration_events;
    while (is_observing) {
        for (auto const& event_filename : std::filesystem::directory_iterator(mEvent_directory)) {
            if (last_iteration_events.find(event_filename) != last_iteration_events.end())
                last_iteration_events.insert(event_filename);
        } 
    }
}

/*
Checks if a filename exists in the observed directory
*/
bool EventListener::file_exists(const std::string* filename)
{
    return std::filesystem::exists(mEvent_directory / *filename);
}