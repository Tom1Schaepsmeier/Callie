#include <iostream>
#include <string>
#include <curl/curl.h>
#include "src/event.h"
#include "src/tasks_author.h"

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

    CalendarEvent e1;

    TasksAuthor a1 = TasksAuthor("/home/tom-schaepsmeier/Documents/Projects/TTExport");


    return 0;
}
