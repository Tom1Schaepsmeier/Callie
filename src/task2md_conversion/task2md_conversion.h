#ifndef TASK2MD_CONVERSION
#define TASK2MD_CONVERSION

#include <filesystem>
#include "obsidian_task.h"

std::string convert(const ObsidianTask* task);
void number_task(ObsidianTask* task, const int number);

#endif