#ifndef EVENTS_H

#define EVENTS_H
#define EVENTS_FILE "my_events"

typedef struct Event;

// Event collection
static Event *events = NULL;

// Event-Related Functions
void AddEvent(int priority, char *category, char *title, char *description, time_t due);
void QuickAddEvent(char *title, time_t due);
Event *RemoveEvent(Event *event);
#endif

#ifdef EVENTS_DEBUG_H
void PrintEvent(Event *event);
#endif