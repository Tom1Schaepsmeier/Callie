#include <string>
#include <time.h>

enum Label {
    TOM,
    ANTONIA,
    GEBURTSTAG,
    HUNDE,
    UNI,
    FUSSBALL,
    FAMILIE,
    GEMEINSAM,

};

struct CalendarEvent {
    std::string calendar;
    std::string headline;
    time_t start_time;
    time_t end_time;
    Label label;
    std::string location;
};

