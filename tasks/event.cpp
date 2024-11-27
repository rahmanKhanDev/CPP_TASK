#include <iostream> 
#include <queue> 
#include <random> 
#include <string> 
#include <thread> 
#include <chrono> 
 
class Event { 
public: 
    std::string eventType; 
    int x, y; 
 
    Event(const std::string& type, int xCoord, int yCoord) 
        : eventType(type), x(xCoord), y(yCoord) {} 
}; 
 
void processEvents(std::queue<Event>& events) { 
    while (!events.empty()) { 
        Event event = events.front(); 
        events.pop(); 
 
        if (event.eventType == "Tap") { 
            std::cout << "Tap Event at (" << event.x << ", " << event.y << ")\n"; 
        } else if (event.eventType == "Swipe") { 
            std::cout << "Swipe Event detected: Start (" << event.x << ", " << event.y << ")\n"; 
        } 
    } 
} 
 
int main() { 
    std::queue<Event> eventQueue; 
 
    eventQueue.push(Event("Tap", 50, 100)); 
    eventQueue.push(Event("Swipe", 10, 20)); 
 
    processEvents(eventQueue); 
    return 0; 
} 

 