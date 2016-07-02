#include "events_debug.h"
#include "events.h"
#include "timing.h"
#include <stdio.h>
#include <stdlib.h>


// Debug Functions

void PrintEvent(Event *event)
{
	fprintf(stdout, "\nEvent: %p\n", event);
	fprintf(stdout, "\tstate\t\t%s\n", EventGetState(event) == EVENT_COMPLETE ? "COMPLETE" : "INCOMPLETE");
	fprintf(stdout, "\tpriority\t%d\n", EventGetPriority(event));
	fprintf(stdout, "\tcategory\t%s\n", EventGetCategory(event));
	fprintf(stdout, "\ttitle\t\t%s\n", EventGetTitle(event));
	fprintf(stdout, "\tdescription\t%s\n", EventGetDescription(event));

	struct tm due = EventGetDue(event);
	fprintf(stdout, "\tdue\t\t%s", asctime(&due));
	due = TimeLeft(due);
	fprintf(stderr, "\ttime left\t%d days, %d hours, %d minutes, and %d seconds\n", due.tm_mday, due.tm_hour, due.tm_min, due.tm_sec);
	
	fprintf(stdout, "\tnext\t\t%p\n", EventGetNext(event));
	fprintf(stdout, "\tprior\t\t%p\n\n", EventGetPrior(event));
}

void PrintEvents()
{
	Event *eventPtr = events;

	while (eventPtr)
	{
		PrintEvent(eventPtr);
		//printf("*Event:\t%p\n\t*due: %s\n", eventPtr, asctime(&eventPtr->due));
		eventPtr = EventGetNext(eventPtr);
	}
}


// Main Testing Program

int main() {
	events = NULL;
	struct tm *temp_time = malloc(sizeof(struct tm));

    printf("DEBUG PROGRAM!\n");

	*temp_time = SetTime(7, 7, 1995, 8, 8);
	printf("%s", asctime(temp_time));
	*temp_time = SetTime(7, 7, 2016, 8, 8);
	printf("%s", asctime(temp_time));
	*temp_time = SetTime(7, 1, 2016, 13, 30);
	printf("\n%s", asctime(temp_time));

	// *temp_time = TimeLeft(*temp_time);
	// printf("\tDays: %d\tHours: %d\tMinutes: %d\tSeconds: %d\n", temp_time->tm_mday, temp_time->tm_hour, temp_time->tm_min, temp_time->tm_sec);

	// \r returns to 0 horizontal
	AddEvent(5, "Housing", "Drop Off Checks", "Rent $625, Deposit $900", *temp_time);
	//PrintEvents();

	//printf("---\n");

	*temp_time = SetTime(7, 1, 2016, 18, 45);
	AddEvent(7, "Food", "Determine Dinner", "Petra, Raku Ramen, etc.", *temp_time);
	//PrintEvents();

	//printf("---\n");

	*temp_time = SetTime(7, 2, 2016, 12, 0);
	AddEvent(9, "Holiday", "Birthday Plans", "Bar? Party? Booze?", *temp_time);
	PrintEvents();

	printf("---\n");

	EventSetState(EventGetNext(EventGetNext(events)), EVENT_COMPLETE);
	PrintEvents();
	return 1;
}