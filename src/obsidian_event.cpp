#include <ctime>
#include <memory>
#include <string>

#include "obsidian_event.h"
#include "timetree_task.h"

ObsidianEvent::ObsidianEvent(const TimeTreeTask* tt_task) : id(tt_task->id),
                                                 name(tt_task->title),
                                                 start_time(tt_task->start_time),
                                                 end_time(tt_task->end_time),
                                                 is_full_day(tt_task->is_full_day),
                                                 notes(tt_task->notes),
                                                 location(tt_task->location)
{
    std::shared_ptr<std::string> event_content = std::shared_ptr<std::string>(new std::string);
    *event_content = "TimeTree\n";
    content = event_content;
}

ObsidianEvent::ObsidianEvent(const std::ifstream*)
{

}

std::shared_ptr<std::string> ObsidianEvent::get_title() const
{}

std::unique_ptr<std::string> convert_to_md() const
{
    
}