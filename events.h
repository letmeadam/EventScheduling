#ifndef EVENTS_H
// /#include <time.h>
#include "timing.h"

#define EVENTS_H
#define EVENTS_FILE "my_events"

#define EVENT_PENDING	0
#define EVENT_OVERDUE	1
#define EVENT_COMPLETE	2

typedef struct Event Event;

// Event Collection
Event *events;

// Event Collection Functions
Event *AddEvent(int priority, char *category, char *title, char *description, struct tm due);
void QuickAddEvent(char *title, struct tm due);
void RemoveEvent(Event *event);

// Event Struct Functions
int EventGetState(Event *event);
int EventGetPriority(Event *event);
char *EventGetCategory(Event *event);
char *EventGetTitle(Event *event);
char *EventGetDescription(Event *event);
struct tm EventGetDue(Event *event);
Event *EventGetNext(Event *event);
Event *EventGetPrior(Event *event);

void EventSetState(Event *event, int state);
void EventSetPriority(Event *event, int priority);
void EventSetCategory(Event *event, char *category);
void EventSetTitle(Event *event, char *title);
void EventSetDescription(Event *event, char *description);
void EventSetDue(Event *event, struct tm due);
void EventSetNext(Event *event, Event *next);
void EventSetPrior(Event *event, Event *prior);
#endif