#include "myh.h"

int countCalls(int invocation[], int month, int maxDate){ // function that counts how many times a command is called in a specific crontab line
	int currCalls = 1;
	if(invocation[0] == -1){										// Minutes given *
		currCalls *= 60;
	}
	if(invocation[1] == -1){										// Hours given *
		currCalls *= 24;
	}

	if(invocation[2] == -1 && invocation[3] != -1){ 			// Day given value, Date given *
		int d;																// The first date that this day occurs
		for(int j = 1; j <= 7; j++){										// Loop to find the first day
			if(dayofweek(2022, month + 1, j) == invocation[3]){
				d = j;
				break;
			}
		}
		currCalls *= 4 + (maxDate % 7 >= d);
	}
	else if(invocation[2] == -1){									// Day given *, Date given *
		currCalls *= maxDate;
	}

	return currCalls;
}

void hoursAndMinutes(int inv[], int startTimes[], int endTimes[], int duration, int *timesIndex, int t_date){ // refer to function below (this was just to eliminate repetitive chunks of code)
	if(inv[1] == -1){
		for(int t_hour = 0; t_hour < 24; t_hour++){
			if(inv[0] == -1){
				for(int t_minute = 0; t_minute < 60; t_minute++){
					startTimes[*timesIndex] = (t_date - 1) * 24 * 60 + t_hour * 60 + t_minute;
					endTimes[*timesIndex] = startTimes[*timesIndex] + duration;
					*timesIndex += 1;
				}
			}
			else{
				int t_minute = inv[0];
				startTimes[*timesIndex] = (t_date - 1) * 24 * 60 + t_hour * 60 + t_minute;
				endTimes[*timesIndex] = startTimes[*timesIndex] + duration;
				*timesIndex += 1;
			}
		}
	}
	else{
		int t_hour = inv[1];
		if(inv[0] == -1){
			for(int t_minute = 0; t_minute < 60; t_minute++){
				startTimes[*timesIndex] = (t_date - 1) * 24 * 60 + t_hour * 60 + t_minute;
				endTimes[*timesIndex] = startTimes[*timesIndex] + duration;
				*timesIndex += 1;
			}
		}
		else{
			int t_minute = inv[0];
			startTimes[*timesIndex] = (t_date - 1) * 24 * 60 + t_hour * 60 + t_minute;
			endTimes[*timesIndex] = startTimes[*timesIndex] + duration;
			*timesIndex += 1;
		}
	}
}

void generateTimes(int startTimes[], int endTimes[], int numInv, int invocations[][5], int executionTimes[], int month, int maxDate){ // function that generates two arrays: one for the start times of every command call and one for the end times
	int timesIndex = 0;
	int duration;

	for(int i = 0; i < numInv; i++){
		duration = executionTimes[invocations[i][4]];

		if(invocations[i][2] == -1 && invocations[i][3] != -1){ 			// Day given value, Date given *
			int d;																// The first date that this day occurs
			for(int j = 1; j <= 7; j++){										// Loop to find the first day
				if(dayofweek(2022, month + 1, j) == invocations[i][3]){
					d = j;
					break;
				}
			}
			for(int t_date = d; t_date <= maxDate; t_date += 7){
				hoursAndMinutes(invocations[i], startTimes, endTimes, duration, &timesIndex, t_date);
			}
		}
		else if(invocations[i][2] == -1){									// Day given *, Date given *
			for(int t_date = 1; t_date <= maxDate; t_date++){
				hoursAndMinutes(invocations[i], startTimes, endTimes, duration, &timesIndex, t_date);
			}
		}
		else{
			int t_date = invocations[i][2];
			hoursAndMinutes(invocations[i], startTimes, endTimes, duration, &timesIndex, t_date);
		}
	}
}

int compareInt(const void *a, const void *b){ // function used when calling qsort to sort the start and end time arrays
  if ( *(int*)a <  *(int*)b ) return -1;
  if ( *(int*)a == *(int*)b ) return 0;
  if ( *(int*)a >  *(int*)b ) return 1;
}
