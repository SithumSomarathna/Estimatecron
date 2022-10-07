#include "myh.h"

int monthtoi(char month[]){ // function that converts any valid value of month into its corresponding integer value

	// an array of possible month strings
	static char monthLabels[24][4] = {"0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};
	
	// check if input month string is a possible month string
	for(int i = 0; i < 24; i++){
		if(strcmp(month, monthLabels[i]) == 0){
			return i % 12;
		}
	}

	// returns -1 if given month string is invalid 
	return -1;
}

int daytoi(char day[]){ // function that converts any valid value of day into its corresponding integer value

	// an array of possible day strings
	static char dayLabels[14][4] = {"0", "1", "2", "3", "4", "5", "6", "sun", "mon", "tue", "wed", "thu", "fri", "sat"};
	
	// check if input day string is a possible day string
	for(int i = 0; i < 14; i++){
		if(strcmp(day, dayLabels[i]) == 0){
			return i % 7;
		}
	}

	// returns -1 if given day string is invalid 
	return -1;
}

bool monthHasDate(int month, int date){ // function that checks if a given month has a given date
	static int numDays[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	return numDays[month] >= date; 
}

int dayofweek(int y, int m, int d){	// function by Tomohiko Sakamoto (ref: https://en.wikipedia.org/wiki/Determination_of_the_day_of_the_week#Sakamoto's_methods) to get day of week from date
    static int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if ( m < 3 )
    {
        y -= 1;
    }
    return (y + y/4 - y/100 + y/400 + t[m-1] + d) % 7;
} // (I could have used system calls to achieve this but I think doing it mathematically is cleaner)