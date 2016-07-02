
plan: main.o events.o
	gcc -Wall -Werror -g -o plan main.o events.o

main.o: main.c
	gcc -Wall -Werror -c main.c

debug: events_debug.o events.o timing.o
	gcc -Wall -o debug events_debug.o events.o timing.o

events_debug.o: events_debug.c
	gcc -Wall -Werror -g -c events_debug.c

events_debug.c: events_debug.h
	touch events_debug.c

events.o: events.c
	gcc -Wall -Werror -g -c events.c

events.c: events.h
	touch events.c

timing.o: timing.c
	gcc -Wall -Werror -g -c timing.c

timing.c: timing.h
	touch timing.c

clean:
	rm *.o plan debug