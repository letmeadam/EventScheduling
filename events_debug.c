#include "events_debug.h"
#include "events.h"
#include "timing.h"
#include <stdio.h>
#include <stdlib.h>

#ifdef EVENTS_DEBUG_H
#define go printf("DEBUG PROGRAM!\n");
#endif

int main() {
	go
	events = NULL;

	struct tm *temp_time = malloc(sizeof(struct tm));

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