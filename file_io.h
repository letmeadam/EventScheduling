#include <stdio.h>

// void OpenFile(FILE *filo, char *file_name);
long FindChar(FILE *filo, long start, char target);
char *ReadSeg(FILE *filo, long start, char target);
char *ReadLine(FILE *filo, long start);
int ReadEvents(FILE *filo);