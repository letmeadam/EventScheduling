#include "timing.h"
#include <stdlib.h>
#include <stdio.h>

struct tm SetTime(int month, int day, int year, int hour, int minute)
{
	time_t raw_time;// = malloc(sizeof(time_t));
		// fprintf(stderr, "(1) raw_time: %p\n", raw_time);
	struct tm *new_time;

	time(&raw_time);
		// fprintf(stderr, "(2) raw_time: %p\n", raw_time);
	new_time = localtime(&raw_time);
		// fprintf(stderr, "(3) raw_time: %p\n", raw_time);
		// fprintf(stderr, "(4) new_time: %p\n", new_time);

	new_time->tm_sec = 0;
	new_time->tm_min = minute;
	new_time->tm_hour = hour;
	new_time->tm_mday = day;
	new_time->tm_mon = month - 1;
	new_time->tm_year = year - 1900;

		// fprintf(stderr, "!(5) ra/w_time: %p\n", raw_time);
		// fprintf(stderr, "!(6) new_time: %p\n", new_time);
	mktime(new_time);
    // printf ("%s", asctime(new_time));
		// fprintf(stderr, "*(7) raw_time: %p\n", raw_time);
		// fprintf(stderr, "*(8) new_time: %p\n", new_time);
    // free(raw_time);
    return *new_time;
}

double SecondsLeft(struct tm due)
{
	time_t cur_time;
	// struct tm time_left;
	double diff = 0.0;
	int days, hours, minutes, seconds;

	time(&cur_time);

	diff = difftime(mktime(&due), cur_time);

	seconds = (int) diff % 60;
	minutes = (int) diff / 60;
	
	hours = minutes / 60;
	minutes = minutes % 60;

	days = hours / 24;
	hours = hours % 24;

	//printf("\tDays: %d\tHours: %d\tMinutes: %d\tSeconds: %d\n", days, hours, minutes, seconds);

    return diff;
}

struct tm TimeLeft(struct tm due)
{
	struct tm time_left;
	double diff = 0.0;
	int days, hours, minutes, seconds;   

	diff = SecondsLeft(due);

	seconds = (int) diff % 60;
	minutes = (int) diff / 60;
	
	hours = minutes / 60;
	minutes = minutes % 60;

	days = hours / 24;
	hours = hours % 24;

	time_left.tm_sec = seconds;
	time_left.tm_min = minutes;
	time_left.tm_hour = hours;
	time_left.tm_mday = days;

    return time_left;
}