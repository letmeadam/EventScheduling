#include "file_io.h"
#include "events.h"
#include <stdio.h>
#include <stdlib.h>

long FindChar(FILE *filo, long start, char target)
{
	unsigned char temp;
	long offset = 0;

	fseek(filo, start, SEEK_SET);

	temp = getc(filo);
	// fprintf(stderr, "%c ?= %c\n", temp, target);
	// fprintf(stderr, "(%c?%c)\n", temp, target);

	while (temp != target && !feof(filo))
	{
		temp = getc(filo);
		// fprintf(stderr, "(%c - %d ? %d) - %ld\n", temp, temp, target, offset+1);
		offset++;
	}

	if (feof(filo) && !offset)
		return -1;					// returns -1 if EOF found

	//fseek(filo, start, SEEK_SET);
	return offset;						// returns target pos from start
}

char *ReadSeg(FILE *filo, long start, char target)
{
	long length = 0;
	char *str, *strptr;

	// fprintf(stderr, "Hit 0\n");
	// fprintf(stderr, "- Filo: %p ?= NULL %s\n", filo, (*filo == NULL) ? "TRUE" : "FALSE");
	rewind(filo);

	if (fseek(filo, start, SEEK_SET))
		fprintf(stderr, "\tERROR: ReadSeg's 1st fseek failed!\n");
	// fprintf(stderr, "Hit 2\n");

	length = FindChar(filo, start, target);
	// fprintf(stderr, "Target (%d) found!\n", target);
	if (-1 == length)
	{
		fprintf(stderr, "ERROR: ReadSeg found/passed EOF\n");
		return NULL;
	}

	// length = length - start;

	if (length < 0)
	{
		fprintf(stderr, "\tERROR: ReadSeg found negative length! %ld\n", length);
		return NULL;
	}
	else if (!length)
	{
		fprintf(stderr, "\tWARNING: ReadSeg found zero length!\n");
		return NULL;
	}
	else
	{
		fseek(filo, start, SEEK_SET);
		str = strptr = malloc(sizeof(char) * (length + 1));

		for (; length > 0; length--)
		{
			*strptr = getc(filo);
			// fprintf(stderr, " %d (%c),", *strptr, *strptr);
			// fflush(stderr);
			strptr++;
		}
		
		*strptr = '\0';			// end string with \0
		// fprintf(stderr, "\n");
		getc(filo);				// read past target

		return str;
	}
}

char *ReadLine(FILE *filo, long start)
{
	return ReadSeg(filo, start, '\n');
}

void ReadEvent(FILE *filo)
{
	Event *new_event;
	int temp_state = EVENT_PENDING;
	int temp_priority = 0;
	char *temp_category, *temp_title, *temp_description;
	time_t temp_due;

	sscanf(ReadSeg(filo, ftell(filo), '|'), "%d", &temp_state);
	sscanf(ReadSeg(filo, ftell(filo), '|'), "%d", &temp_priority);
	temp_category = ReadSeg(filo, ftell(filo), '|');
	temp_title = ReadSeg(filo, ftell(filo), '|');
	temp_description = ReadSeg(filo, ftell(filo), '|');
	sscanf(ReadSeg(filo, ftell(filo), '\n'), "%ld", &temp_due);
	
	new_event = AddEvent(temp_priority, temp_category, temp_title, temp_description, *localtime(&temp_due));
	EventSetState(new_event, temp_state);

	// fprintf(stdout, "\nEvent: %p\n", events);
	// fprintf(stdout, "\tstate\t\t%s\n", EventGetState(events) == EVENT_COMPLETE ? "COMPLETE" : "INCOMPLETE");
	// fprintf(stdout, "\tpriority\t%d\n", EventGetPriority(events));
	// fprintf(stdout, "\tcategory\t%s\n", EventGetCategory(events));
	// fprintf(stdout, "\ttitle\t\t%s\n", EventGetTitle(events));
	// fprintf(stdout, "\tdescription\t%s\n", EventGetDescription(events));

	// struct tm t_due = EventGetDue(events);
	// fprintf(stdout, "\tdue\t\t%s", asctime(&t_due));
	// t_due = TimeLeft(t_due);
	// fprintf(stderr, "\ttime left\t%d days, %d hours, %d minutes, and %d seconds\n", t_due.tm_mday, t_due.tm_hour, t_due.tm_min, t_due.tm_sec);
}

int ReadEvents(FILE *filo)
{
	int event_count = 0;

	while (!feof(filo))
	{
		ReadEvent(filo);
		event_count++;
	}
	return event_count;
}