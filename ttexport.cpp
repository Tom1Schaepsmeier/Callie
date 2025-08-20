#include <iostream>
#include <string>
#include <curl/curl.h>
#include <ctime>
#include "src/obsidian_event.h"
#include "src/timetree_task.h"

int main() {

    // CURL *curl = curl_easy_init();
    // if (curl) {
    //     CURLcode res;
    //     curl_easy_setopt(curl, CURLOPT_URL, "https://timetreeapp.com/intl/en");
    //     res = curl_easy_perform(curl);
    //     curl_easy_cleanup(curl);
    // }

    // get all data from TimeTree
    //TTClient ttClient = TTClient("", "");

    // store data properly

    // convert data into different format
    srand(time(nullptr));
    std::string title = "Hello world";
    tm start_time;
    start_time.tm_year = 2025;
    start_time.tm_mon = 02;
    start_time.tm_mday = 12;
    tm end_time = start_time;
    TimeTreeTask task = TimeTreeTask(&title, &start_time, &end_time, false);
    TimeTreeTask t2 = TimeTreeTask(&title, &start_time, &end_time, false);
    if (!(task == t2))
        std::cout << "ha" << std::endl;
}
