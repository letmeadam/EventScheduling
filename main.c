#include <stdio.h>
#include <stdlib.h>

// #define EVENT_FILE "my_events"

int main()
{
	FILE *filo;

	if (NULL == (filo = fopen(EVENT_FILE, "r")))
		return EXIT_FAILURE;

	while (0 < fscanf(filo, "%d_%s_", ... ))
	{
		a
	}

    return EXIT_SUCCESS;
}
