#include <stdio.h>
#include <stdlib.h>
#include "events.h"
#include "file_io.h"

#define EVENT_FILE "my_events"

int main()
{
	printf("MAIN PROGRAM!\n");

	int state, priority;
	char *category, *title, *description;
	time_t due;

	category = malloc(sizeof(char) * 100);
	title = malloc(sizeof(char) * 100);
	description = malloc(sizeof(char) * 100);

	fscanf(stdin, IO_FORMAT, &state, &priority, category, title, description, &due);
    AddEvent(priority, category, title, description, *localtime(&due));
	printf("DONE!\n");

	fprintf(stdout, "\nEvent: %p\n", events);
	fprintf(stdout, "\tstate\t\t%s\n", EventGetState(events) == EVENT_COMPLETE ? "COMPLETE" : "INCOMPLETE");
	fprintf(stdout, "\tpriority\t%d\n", EventGetPriority(events));
	fprintf(stdout, "\tcategory\t%s\n", EventGetCategory(events));
	fprintf(stdout, "\ttitle\t\t%s\n", EventGetTitle(events));
	fprintf(stdout, "\tdescription\t%s\n", EventGetDescription(events));

	struct tm t_due = EventGetDue(events);
	fprintf(stdout, "\tdue\t\t%s", asctime(&t_due));
	t_due = TimeLeft(t_due);
	fprintf(stderr, "\ttime left\t%d days, %d hours, %d minutes, and %d seconds\n", t_due.tm_mday, t_due.tm_hour, t_due.tm_min, t_due.tm_sec);
	
	fprintf(stdout, "\tnext\t\t%p\n", EventGetNext(events));
	fprintf(stdout, "\tprior\t\t%p\n\n", EventGetPrior(events));

    return EXIT_SUCCESS;
}
