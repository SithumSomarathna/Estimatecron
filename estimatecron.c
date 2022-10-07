//  CITS2002 Project 1 2022
//  Student1:   23614803   SOMARATHNA   SITHUM
//	Student2:	------------------------------
#include "myh.h"

#define DEBUG false

int main(int argc, char *argv[])
{
	////////////////////////////////// Ensure valid inputs to main() ////////////////////////////////////////////////
	
	if(argc != 4) {																							// check for correct number of inputs
        printf("%s: program expected 4 arguments, but instead received %d\n", argv[0], argc-1);
        exit(EXIT_FAILURE);
    }
																									
    int month = monthtoi(argv[1]);
    int maxDate;
    if(month == -1) {																						// check for valid month input
    	printf("%s: program expected a valid month, but instead received %s\n", argv[0], argv[1]);
    	exit(EXIT_FAILURE);
    }
    else{																									// calculate the maximum date in this month
		for(int i = 0; i <= 31; i++){
			if(!monthHasDate(month, i+1)){
				maxDate = i;
				break;
			}
		}
    }

    ////////////////////////////////// Read files and store data ////////////////////////////////////////////////

	char commandNames[20][41];													// An array with all the command names in the estimates file
	int executionTimes[20];														// An array with all the execution times in the estimates file
	int definedCommands;														// The number of defined commands in the estimates file

	readEstimates(argv[3], commandNames, executionTimes, &definedCommands);		// Read the estimates file and put information into corresponding arrays

	if(DEBUG){
	    printArrS("commandNames", &commandNames[0][0], definedCommands, sizeof(commandNames[0]));
	    printArrI("executionTimes", executionTimes, definedCommands);
	}

    int invocations[20][5]; 															// An array with all the invokation details. In format [minute, hour, date, day, command index]
    int numInv; 																		// The number of defined elements in the invocations array

    readCrontab(argv[2], invocations, &numInv, month, definedCommands, commandNames);	// Read the crontab file and put information in to the invocations array

    if(DEBUG){
	    for(int i = 0; i < numInv; i++){
	    	printArrI("invocations", invocations[i], 5);
		}
	}


	////////////////////////////////// Determine most frequently called command and total command calls ////////////////////////////////////////////////

	int callCount[definedCommands];														// An array to keep count of how many times each command is called. The index of each count will match the index of its respective command in the commandNames array
	memset(callCount, 0, definedCommands*sizeof(int));

	for(int i = 0; i < numInv; i++){

		callCount[invocations[i][4]] += countCalls(invocations[i], month, maxDate);		// The number of times a command is called from a single invocation statement throughout the month is calculated
																						// and the result is added to the total count of how many times that command in called in the month
	}

	if(DEBUG){
		printArrI("callCount", callCount, definedCommands);
	}

	int maxCalls = 0;
	int commandIndex;
	int totalCalls = 0;

	for(int i = 0; i < definedCommands; i++){				// Iterate through all the call counts for each command and determine the maximum 
		if(callCount[i] > maxCalls){
			maxCalls = callCount[i];
			commandIndex = i;
		}
		totalCalls += callCount[i];
	}

	printf("Most frequently executed command: %s\nTotal number of commands invoked: %i\n", commandNames[commandIndex], totalCalls);

	////////////////////////////////// Determine maximum concurrent commands ////////////////////////////////////////////////

	int startTimes[totalCalls];			// An array that will hold the start times of every command call (start time is measured as the number of seconds since the beginning of the month)
	int endTimes[totalCalls];			// An array that will hold the end times of every command call (end time is measured as the number of seconds since the beginning of the month)

	generateTimes(startTimes, endTimes, numInv, invocations, executionTimes, month, maxDate);	// Determines the start and end times of each command call and writes them into the two arrays

	qsort(startTimes, totalCalls, sizeof(int), compareInt);				//
	qsort(endTimes, totalCalls, sizeof(int), compareInt);				// Sorts each array such that the times are in order

	//printArrI("startTimes", startTimes, totalCalls);
	//printArrI("endTimes", endTimes, totalCalls);

	int st_index = 0;
	int et_index = 0;
	int conc = 0;
	int maxConc = 0;

	while(st_index < totalCalls){							// Count the number of commands currently running: If we hit a start time, then the concurrent number increases and if we hit an end time the concurrent number decreases
		if(startTimes[st_index] < endTimes[et_index]){ 			// A new process starts before a running process ends
			conc++;
			if(conc > maxConc){
				maxConc = conc;
			}
			st_index++;
		}
		else{													// A running process ends before a new process starts
			conc--;
			et_index++;
		}
	}

	printf("Max concurrency: %i\n", maxConc);

    return EXIT_SUCCESS;
}