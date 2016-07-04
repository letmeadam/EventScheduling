#include "file_io.h"
#include <stdio.h>
#include <stdlib.h>

void OpenFile(FILE *filo, char *file_name)
{
	filo = fopen(file_name, "r+");

	if (NULL == filo)
		fprintf(stderr, "\tERROR: Unable to open file \"%s\".\n", file_name);
	perror(NULL);
}


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