#include <fstream>
#include <iostream>
#include <iomanip>
#include <queue>
#include <algorithm>

using namespace std;

struct Event
{
    int time;
    int serving;
    Event(int t, int w);
};

Event::Event(int t, int w){
    time = t;
    serving = w;
}

struct EventList
{
    int count;

    priority_queue<Event> events;
    void fill(istream& is);
    void simulate();
};

bool operator<(const Event &first, const Event &second)
{
    return second.time < first.time;
}

int main(int argc, char** argv)
try {
    EventList eventList;
    char* progname = argv[0];
    switch (argc) {
        case 1:
            eventList.fill(cin);
            break;
        case 2: {
            ifstream ifs(argv[1]);
            if (!ifs) {
                cerr << progname << ": couldn't open "
                << argv[1] << endl;
                return 1;
                }
                eventList.fill(ifs);
                break;
                }
            default:
                cerr << "Usage: " << progname << " [datafile]\n";
                return 2;
                }
                eventList.simulate();
                }
                catch (int e){
                    return e;
                }
                
void EventList::fill(istream& is)
{
    int arrival = 0;
    int time = 0;
    int most_recent_time = 0;
    Event evn(arrival, time);
    count = 0;
                    
    while(is >> arrival >> time) {
    count++;
    most_recent_time = evn.time;
    evn.time = arrival;
    evn.serving = time;
    if(most_recent_time > evn.time) {
    cerr << "customer #" << count
    << " out of order (time = "
    << evn.time << ", previous time = "
    << most_recent_time << ")" << endl;
    throw 3; // exit status 3
}
    events.push(evn);
}
}
                
void EventList::simulate()
{
    int open_time = 0;
    int total_wait = 0;
                    
    while(!events.empty()) {
    Event e = events.top();
    events.pop();
    if(e.serving >= 0){
    open_time = max(e.time, open_time);
    total_wait += open_time - e.time;
    open_time += e.serving;
    Event depart(open_time, -1);
    events.push(depart);
    cout << "Processing an arrival event at time:"
    << setw(5) << e.time << endl;
}
else {
        cout << "Processing a departure event at time:"
        << setw(4) << e.time  << endl;
}
    }
    cout << endl << "Final statistics:" << endl;
    cout << setw(41) << "Total number of people processed:     ";
    cout << count << endl;
    cout << setw(41) << "Average amount of time spent waiting: "
    << (double)total_wait/count << endl;
}
