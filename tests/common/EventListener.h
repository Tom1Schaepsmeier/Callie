#ifndef EVENT_LISTENER_H
#define EVENT_LISTENER_H

#include <filesystem>
#include <vector>

class EventListener {

    std::filesystem::path mEvent_directory;
    std::vector<std::filesystem::path> mAdded_files;
    bool is_observing;

    void observe_event_directory();

    public:
       /*
       Default constructor
       */
       EventListener(std::string* event_directory);

       /*
       Copy Constructor
       */
       EventListener(const EventListener& event_observer);

       /*
       Move Constructor
       */
       EventListener(EventListener&& event_observer);

       /*
       Destructor
       */
       ~EventListener();

       /*
       Starts observing the directory for file changes
       */
       void start();

       /*
       Stops the observation process
       */
       void stop();

       /*
       Retrieves all file names which were added during the observation process
       */
       std::vector<std::filesystem::path> retrieve_added_files();  
       
       /*
       Checks if a given filename exists in the observed directory
       */
       bool file_exists(const std::string* filename);
};


#endif