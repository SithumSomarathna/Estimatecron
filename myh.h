#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

extern int monthtoi(char*); // function that converts any valid value of month into its corresponding integer value

extern int daytoi(char*); // function that converts any valid value of day into its corresponding integer value

extern bool monthHasDate(int, int); // function that checks if a given month has a given date

extern void printArrS(char*, char*, int, int); // function prints an array of strings in the form "arrayName: [element1, element2, element3, ...]"   (Used for debugging)

extern void printArrI(char*, int*, int); // function prints an array of integers in the form "arrayName: [element1, element2, element3, ...]"   (Used for debugging)

extern int dayofweek(int, int, int);	// function by Tomohiko Sakamoto (ref: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto's_methods) to get day of week from date

extern void readEstimates(char*, char(*)[41], int*, int*); // function that reads and collects data from the estimates file

extern void readCrontab(char*, int(*)[5], int*, int, int, char(*)[41]); // function that reads and collects data from the crontab file

extern int countCalls(int*, int, int); // function that counts how many times a command is called in a specific crontab line

extern void hoursAndMinutes(int*, int*, int*, int, int*, int); // refer to function below (this was just to eliminate repetitive chunks of code)

extern void generateTimes(int*, int*, int, int(*)[5], int*, int, int); // function that generates two arrays: one for the start times of every command call and one for the end times

extern int compareInt(const void*, const void*); // function used when calling qsort to sort the start and end time arrays