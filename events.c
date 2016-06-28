#include "events.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct Event
{
	int priority;
	char *category;
	char *title;
	char *description;
	time_t due;
	Event *next;
	Event *prior;
} Event;

void InsertEvent(Event *event)
{
	/* I should fix this to recalculate priority values each time - especially if found equal
	 *  priority value!
	 */
	Event *eventPtr = events;

	if (NULL == eventPtr)
	{
		events = event;
		return;
	}

	while(eventPtr)
	{
		if (event->priority < eventPtr->priority)	//if 'event' is less important...
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
void AddEvent(int priority, char *category, char *title, char *description, time_t due)
{
	Event *newEvent;
	Event *eventPtr = events;

	if (NULL == (newEvent = malloc(sizeof(Event))))
	{
		fprintf(stderr, "ERROR: Unable to malloc new Event.\n");
		return;
	}

	newEvent->priority = priority;
	newEvent->category = category;
	newEvent->title = title;
	newEvent->description = description;
	newEvent->due = due;
	newEvent->next = newEvent->prior = NULL;

	InsertEvent(newEvent);
}


void QuickAddEvent(char *title, time_t due)
{
	AddEvent(0, "\0", title, "\0", due);
}

Event *CompareEvent(Event *event1, Event *event2)
{
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
			if (event1->due == event2->due)
				return NULL;
			else if (event1->due < event2->due)
				return event1;
			else
				return event2;
		}
	}
}

void RemoveEvent(Event * event)
{
	/* Need to change input parameter to be more specific (i.e. Title) 
	 *  NOTE: if I change that parameter, I also need to change CompareEvent
	 *        to match based on that specification
	 */
	Event * eventPtr = events;

	while (eventPtr && CompareEvent(evenPtr, event)) {
		eventPtr = eventPtr->next;
	}

	if (!eventPtr)
	{
		fprintf(stderr, "WARNING: Event not found.\n");
		return;
	}

	if (NULL == CompareEvent(eventPtr, event))
	{
		if (eventPtr->prior)						//if prior exists
			eventPtr->prior->next = eventPtr->next;		//prior's next points to current's next
		else										//else current Event is head of list
			events = eventPtr->next;
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

#ifdef EVENTS_DEBUG_H

void PrintEvent(Event *event)
{
	fprintf(stdout, "Event %p:\n", event);
	fprintf(stdout, "\tpriority\t%d\n", event->priority);
	fprintf(stdout, "\tcategory\t%s\n", event->category);
	fprintf(stdout, "\title\t%s\n", event->title);
	fprintf(stdout, "\tdescription\t%s\n", event->description);
	fprintf(stdout, "\tdue\t%ld\n", event->due);
	fprintf(stdout, "\tnext\t%p\n", event->next);
	fprintf(stdout, "\tprior\t%p\n", event->prior);
}
#endif