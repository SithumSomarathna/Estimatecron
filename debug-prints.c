#include "myh.h"

void printArrS(char name[], char *first, int size, int length){ // function prints an array of strings in the form "arrayName: [element1, element2, element3, ...]"   (Used for debugging)
	printf("%s: [%s", name, first);
	
	for(int i = 1; i < size; i++){
		printf(", %s", first + length * i);
	}
	
	printf("]\n");
}

void printArrI(char name[], int ints[], int size){ // function prints an array of integers in the form "arrayName: [element1, element2, element3, ...]"   (Used for debugging)
	printf("%s: [%i", name, ints[0]);
	
	for(int i = 1; i < size; i++){
		printf(", %i", ints[i]);
	}
	
	printf("]\n");
}