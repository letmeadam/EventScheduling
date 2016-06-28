/* asctime example */
#include <stdio.h>      /* printf */
#include <time.h>       /* time_t, struct tm, time, localtime, asctime */

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime ( &rawtime );
  printf ( "The current date/time is: %s", asctime (timeinfo) );
  printf ( "Computer sees this date/time as: %ld\n", rawtime);

  return 0;
}