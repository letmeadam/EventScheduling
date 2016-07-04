#include "events.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Event
{
	int state;
	int priority;
	char *category;
	char *title;
	char *description;
	struct tm due;
	Event *next;
	Event *prior;
} Event;


// Helper Functions

Event *CompareEvent(Event *event1, Event *event2)
{
	double diff = 0;

	if (!event1 && !event2)
		return NULL;
	else if (!event1 && event2)
		return event2;
	else if (event1 && !event2)
		return event1;
	else
	{
		if (event1->priority < event2->priority)
			return event2;
		else if (event1->priority > event2->priority)
			return event1;
		else
		{
			diff = difftime(mktime(&event1->due), mktime(&event2->due));
			if (0.0 == diff)
				return NULL;
			else if (0.0 > diff) //if event1 is due sooner
				return event1;
			else
				return event2;
		}
	}
}

void InsertEvent(Event *event)
{
	/* I should fix this to recalculate priority values each time - especially if found equal
	 *  priority value!
	 */
	Event *victor, *eventPtr = events;

	if (NULL == eventPtr)
	{
		events = event;
		return;
	}

	while(eventPtr)
	{
		// NOTE: to revers order, simply replace to "victor == event"
		victor = CompareEvent(event, eventPtr);

		if (victor != event)	//if 'event' is less important...
		{
			if (!eventPtr->next)						//if currently at last event in list...
			{
				eventPtr->next = event;						//set next event to new 'event'
				event->prior = eventPtr;					//set new 'event's prior to original last event
				return;											//END LOOP
			}
			else										//else if currently mid-list...
				eventPtr = eventPtr->next;					//move on to next event
		}
		else										//if 'event' is more/equally important...
		{
			event->prior = eventPtr->prior;				//set new 'event's prior to current event's prior
			event->next = eventPtr;						//set new 'event's next to current event
			eventPtr->prior = event;					//set less important event's prior to new 'event'
			// events = event;

			if(eventPtr == events)						//if currently at beginning of list...
			{
				// event->next = eventPtr;						//set new 'event's next to first event
				// eventPtr->prior = event;					//set first event's prior to new 'event'
				events = event;								//set beginning of list to new 'event'
				// return;											//END LOOP
			}
			/*else										//else mid-list...
			{
				event->prior = eventPtr->prior;				//set new 'event's prior to current event's prior
				event->next = eventPtr;						//set new 'event's next to current event
				eventPtr->prior = event;					//set less important event's prior to new 'event'
				return;											//END LOOP
			}*/

			return;
		}
	}
}


// Event-Related Functions

Event *AddEvent(int priority, char *category, char *title, char *description, struct tm due)
{
	Event *newEvent;
	// Event *eventPtr = events;

	if (NULL == (newEvent = malloc(sizeof(Event))))
	{
		fprintf(stderr, "ERROR: Unable to malloc new Event.\n");
		return NULL;
	}

	newEvent->state = EVENT_PENDING;
	newEvent->priority = priority;
	newEvent->category = category;
	newEvent->title = title;
	newEvent->description = description;
	newEvent->due = due;
	newEvent->next = newEvent->prior = NULL;

	// printf("Before insert: %p\n", events);
	InsertEvent(newEvent);
	// printf("After insert: %p\n", events);
	return newEvent;
}


void QuickAddEvent(char *title, struct tm due)
{
	AddEvent(0, "\0", title, "\0", due);
}

void RemoveEvent(Event * event)
{
	/* Need to change input parameter to be more specific (i.e. Title) 
	 *  NOTE: if I change that parameter, I also need to change CompareEvent
	 *        to match based on that specification
	 */
	Event * eventPtr = events;

	while (eventPtr && CompareEvent(eventPtr, event)) {
		eventPtr = eventPtr->next;
	}

	// fprintf(stderr, "Event found: %p = %p\n", eventPtr, event);

	if (!eventPtr)
	{
		fprintf(stderr, "WARNING: Event not found.\n");
		return;
	}

	if (NULL == CompareEvent(eventPtr, event))
	{
		// fprintf(stderr, "Event->prior %p\n", eventPtr->prior);
		if (eventPtr->prior)						//if prior exists
			eventPtr->prior->next = eventPtr->next;		//prior's next points to current's next
		else										//else current Event is head of list
			events = eventPtr->next;

		// fprintf(stderr, "Event->next %p\n", eventPtr->next);
		if (eventPtr->next)							//if next exists
			eventPtr->next->prior = eventPtr->prior;	//next's prior points to current's prior

		free(eventPtr);								//remove Event from memory
	}
	else
	{
		fprintf(stderr, "ERROR: Unable to Remove Event.\n");
		return;
	}
}


// Event Struct Functions

int EventGetState(Event *event)
{
	return event->state;
}

int EventGetPriority(Event *event)
{
	return event->priority;
}

char *EventGetCategory(Event *event)
{
	return event->category;
}

char *EventGetTitle(Event *event)
{
	return event->title;
}

char *EventGetDescription(Event *event)
{
	return event->description;
}

struct tm EventGetDue(Event *event)
{
	return event->due;
}

Event *EventGetNext(Event *event)
{
	return event->next;
}

Event *EventGetPrior(Event *event)
{
	return event->prior;
}


void EventSetState(Event *event, int state)
{
	event->state = state;
}

void EventSetPriority(Event *event, int priority)
{
	event->priority = priority;
}

void EventSetCategory(Event *event, char *category)
{
	event->category = category;
}

void EventSetTitle(Event *event, char *title)
{
	event->title = title;
}

void EventSetDescription(Event *event, char *description)
{
	event->description = description;
}

void EventSetDue(Event *event, struct tm due)
{
	event->due = due;
}

void EventSetNext(Event *event, Event *next)
{
	event->next = next;
}

void EventSetPrior(Event *event, Event *prior)
{
	event->prior = prior;
}
