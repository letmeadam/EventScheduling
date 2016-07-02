#include "file_io.h"

FILE *filo;

	if (NULL == (filo = fopen(EVENT_FILE, "r")))
		return EXIT_FAILURE;

	while (0 < fscanf(filo, "%d_%s_", ... ))
	{
		h
	} 