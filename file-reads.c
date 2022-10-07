#include "myh.h"

void readEstimates(char *filename, char commandNames[20][41], int *executionTimes, int *definedCommands){ // function that reads and collects data from the estimates file
	// attempt to open estimates file
	char line[101];

    FILE *estimates = fopen(filename, "r");
    if(estimates == NULL){
    	printf("%s: file failed to open\n", filename);
    	exit(EXIT_FAILURE);
    }

    // file successfully opened
    else{
    	
    	int arrayIndex = 0;

    	// read lines of files and store into arrays
    	while(fgets(line, sizeof(line), estimates) != NULL){ 

    		// iterate through string until a non-white space is found
    		for(int i = 0; i < sizeof(line); i++){
    			if(line[i] != ' ' && line[i] != '\t'){
    				if(line[i] != '#'){
    					
    					// a non-comment line has been found, put values into arrays if they are valid
    					char *token = strtok(line, " \t\n\r");
    					int numtokens = 1;
    					while(token != NULL){
    						switch(numtokens){
    							case 1: // this should be the name of the command
    								if(!isalpha(token[0])){
    									printf("%s\n", token);
			    						printf("%s: incorrect file format: invalid command name\n", filename);
			    						exit(EXIT_FAILURE);
	    							}
	    							strcpy(commandNames[arrayIndex], token);
	    							break;

	    						case 2: // this should be execution time
	    							if(atoi(token) <= 0){
	    								printf("%s: incorrect file format: invalid execution time\n", filename);
	    								exit(EXIT_FAILURE);
	    							}
	    							executionTimes[arrayIndex] = atoi(token);
	    							arrayIndex++;
	    							break;

	    						default:
	    							if(!isspace(token[0])){
	    								printf("%s: incorrect file format: each line should only have two values\n", filename);
    									exit(EXIT_FAILURE);
	    							}
    						}

    						numtokens++;
    						token = strtok(NULL, " \t\n\r");
    					}
    					if(numtokens < 2){
    						printf("%s: incorrect file format: execution time not speficied\n", filename);
    						exit(EXIT_FAILURE);
    					}
    				}
    				break;
    			}
    		}			
    	}

    	// Record the number of commands that have been defined
    	*definedCommands = arrayIndex;
    }

    fclose(estimates);
}

void readCrontab(char *filename, int invocations[20][5], int *numInv, int month, int definedCommands, char commandNames[20][41]){ // function that reads and collects data from the crontab file
	char line[101];

	// attempt to open crontab file
    FILE *crontab = fopen(filename, "r");
    if(crontab == NULL){
    	printf("%s: failed to open file\n", filename);
    	exit(EXIT_FAILURE);
    }

    else{

    	int arrayIndex = 0;

    	// read lines of files and store into arrays
    	while(fgets(line, sizeof(line), crontab) != NULL){ 
    		
    		// iterate through string until a non-white space is found
    		for(int i = 0; i < sizeof(line); i++){
    			if(line[i] != ' ' && line[i] != '\t'){
    				if(line[i] != '#'){
    					
    					// a non-comment line has been found, put values into arrays if they are valid
    					char *token = strtok(line, " \t\n\r");
    					int numtokens = 1;
    					bool disregard = false;
    					while(token != NULL){
    						
    						switch(numtokens){

    							case 1: // this should be the minutes
    								if(strcmp(token, "*") == 0){
    									invocations[arrayIndex][0] = -1;
    								}
    								else if(isdigit(token[0])){
	    								invocations[arrayIndex][0] = atoi(token);
	    							}
	    							else{
	    								printf("%s: incorrect file format: invalid minutes\n", filename);
	    								exit(EXIT_FAILURE);
	    							}
    								break;
    							case 2: // this should be the hours
    								if(strcmp(token, "*") == 0){
    									invocations[arrayIndex][1] = -1;
    								}
    								else if(isdigit(token[0])){
    									invocations[arrayIndex][1] = atoi(token);
    								}
	    							else{
	    								printf("%s: incorrect file format: invalid hours\n", filename);
	    								exit(EXIT_FAILURE);
	    							}
    								break;
    							case 3: // this should be the date
    								if(strcmp(token, "*") == 0){
    									invocations[arrayIndex][2] = -1;
    								}	
    								else if(atoi(token) > 0){
	    								invocations[arrayIndex][2] = atoi(token);
	    							}
	    							else{
	    								printf("%s: incorrect file format: invalid date\n", filename);
	    								exit(EXIT_FAILURE);
	    							}
    								break;
								case 4: // this should be the month
									if(strcmp(token, "*") != 0){
										if(monthtoi(token) < 0){
											printf("%s: incorrect file format: invalid month\n", filename);
		    								exit(EXIT_FAILURE);
		    							}
		    							else if(monthtoi(token) != month){		// If the month in this line is not the month we are interested in then we should not bother analysing it
		    								disregard = true;
		    							}
									}
    								break;
    							case 5: // this should be the day of the week
    								if(strcmp(token, "*") == 0){
    									invocations[arrayIndex][3] = -1;
									}
									else if(daytoi(token) >= 0){
										
										int date = invocations[arrayIndex][2];
										if(date != -1){							// If the combination of date and day of week in this line does not occur in this month during 2022 then we should not bother analysing it
											if(dayofweek(2022, month + 1, date) != daytoi(token)){
												disregard = true;
											}
										}
										
										invocations[arrayIndex][3] = daytoi(token);
									}
									else{
										printf("%s: incorrect file format: invalid day of the week\n", filename);
	    								exit(EXIT_FAILURE);
									}
    								break;
    							case 6: ; // this should be the program name
    									bool found = false;
    									for(int i = 0; i < definedCommands; i++){ // Attempt to find this program in the array of defined commands

    										if(strcmp(commandNames[i], token) == 0){
    											found = true;
    											invocations[arrayIndex][4] = i;
    											break;
    										}
    									}
    									if(!found){
    										printf("%s: incorrect file format: invalid command name\n", filename);
    										printf("%s\n", token);
	    									exit(EXIT_FAILURE);
    									}
    									if(!disregard){
    									// If the current line needs to be disregarded, then by not incrementing arrayIndex we can overwrite the values of this line with the ones of the next line
    										arrayIndex++;
    									}
    								break;

    							default:
	    							if(!isspace(token[0])){
	    								printf("%s: incorrect file format: each line should only have six values\n", filename);
    									exit(EXIT_FAILURE);
	    							}
    						}
    						token = strtok(NULL, " \t\n\r");
    						numtokens++;
    					}
    					if(numtokens < 6){
    						printf("%s: incorrect file format: wrong number of arguments in line\n", filename);
    						exit(EXIT_FAILURE);
    					}
    				}
    				break;
    			}
    		}
    	}

    	// numInv is essentially the number of useful lines in this file that will contribute to analysis
    	*numInv = arrayIndex;
    }

    fclose(crontab);
}