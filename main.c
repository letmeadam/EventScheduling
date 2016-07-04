#include <stdio.h>
#include <stdlib.h>
#include "events.h"
#include "file_io.h"

#define EVENT_FILE "my_events"

// state|priority|category|title|description|due
// consider using date format (i.e. ...|Jul|7|2016|12|0|0 )

int main()
{
	FILE *filo = NULL;
	int temp_state = EVENT_PENDING;
	int temp_priority = 0;
	char *temp_category, *temp_title, *temp_description;
	time_t temp_due;

	printf("MAIN PROGRAM!\n");

	filo = fopen(EVENT_FILE, "r+");

	if (NULL == filo)
		fprintf(stderr, "\tERROR: Unable to open file \"%s\".\n", EVENT_FILE);

	// printf("\n1: %s\n", ReadLine(filo, 0));
	// printf("\n2: %s\n", ReadLine(filo, ftell(filo)));
	// printf("\n3: \n\tstate:\t\t%s\n", ReadSeg(filo, ftell(filo), '|'));
	// printf("\tpriority:\t%s\n", ReadSeg(filo, ftell(filo), '|'));
	// printf("\tcategory\t%s\n", ReadSeg(filo, ftell(filo), '|'));
	// printf("\ttitle\t\t%s\n", ReadSeg(filo, ftell(filo), '|'));
	// printf("\tdescription\t%s\n", ReadSeg(filo, ftell(filo), '|'));
	// printf("\tdue\t\t%s\n", ReadSeg(filo, ftell(filo), '\n'));
	// printf("\n4: %s\n", ReadLine(filo, ftell(filo)));
	// printf("\n5: (EOF) %s\n", ReadLine(filo, ftell(filo)));
	
	// // int state, priority;
	// char *category, *title, *description;
	// time_t due;

	// category = malloc(sizeof(char) * 100);
	// title = malloc(sizeof(char) * 100);
	// description = malloc(sizeof(char) * 100);

	// fscanf(stdin, IO_FORMAT, &state, &priority, category, title, description, &due);
    // AddEvent(priority, category, title, description, *localtime(&due));
	// printf("DONE!\n");

	sscanf(ReadSeg(filo, 0, '|'), "%d", &temp_state);
	sscanf(ReadSeg(filo, ftell(filo), '|'), "%d", &temp_priority);
	// temp_priority = sprintf("%d", ReadSeg(filo, ftell(filo)));
	temp_category = ReadSeg(filo, ftell(filo), '|');
	temp_title = ReadSeg(filo, ftell(filo), '|');
	temp_description = ReadSeg(filo, ftell(filo), '|');
	// temp_due = (time_t) sprintf("%d", ReadSeg(filo, ftell(filo), '\n'));
	sscanf(ReadSeg(filo, ftell(filo), '\n'), "%ld", &temp_due);
	AddEvent(temp_priority, temp_category, temp_title, temp_description, *localtime(&temp_due));
	EventSetState(events, temp_state);

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

	// printf("%ld\n", time(NULL));
	
	// fprintf(stdout, "\tnext\t\t%p\n", EventGetNext(events));
	// fprintf(stdout, "\tprior\t\t%p\n\n", EventGetPrior(events));

	// free(filo);
	fclose(filo);
    return EXIT_SUCCESS;
}
