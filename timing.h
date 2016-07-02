#include <time.h>

struct tm SetTime(int month, int day, int year, int hour, int minute);

double SecondsLeft(struct tm due);
struct tm TimeLeft(struct tm due);