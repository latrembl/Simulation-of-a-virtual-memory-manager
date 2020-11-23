#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BUFLEN 256
#define PAGE_SIZE 256
#define	ADDRESS_RANGE 65535

int decodeAddress(int address, int *pageNumber, int *pageOffset) {
	//printf("\nDecoding Address %i...\n", address);
	if (address > ADDRESS_RANGE || address < 0) {
		printf("ERROR: Address not in range. \n");
		return -1;
	} else {
		*pageNumber = address / PAGE_SIZE;
		*pageOffset = address % PAGE_SIZE;
		
		//printf("Inside decodeAddress() --- Page Number: %d \n", *pageNumber);
		//printf("Inside decodeAddress() --- Page Offset: %d \n", *pageOffset);
		//printf("Decoding Complete! \n");
	}
	return 0;
}

int readFromBackingStore(FILE **fp, unsigned char *buffer, int pageNumber) {
	//printf("\nReading from file...\n");
	//printf("Inside readFromBackingStore() --- Page Number: %i \n", pageNumber);
	
	int rtnval;
	long offset;
		
	offset = PAGE_SIZE * pageNumber;		
	
	rtnval = fseek(*fp, offset, 0);	
	//printf("Inside readFromBackingStore() --- Seek return value: %i \n", rtnval);
	
	if (rtnval != 0) {
		printf("File Seek Failed! \n");
		return (rtnval);
	}	
	
	rtnval = fread(buffer, 1, PAGE_SIZE, *fp);
	//printf("Inside readFromBackingStore() --- Read return value: %i \n", rtnval);
	
	if (rtnval != PAGE_SIZE) {
		printf("Reading Failed! \n");
		return(1);
	}	else {		
		//printf("Reading Complete! \n");
		return(0);
	}	
}

int main() {
	
	int address = 0;
	int *pageNumber =0;
	int *pageOffset =0;
	unsigned char buffer[BUFLEN];
	unsigned char buffer2[BUFLEN];
	char *infile = "addresses.txt";	
	char *fname = "BACKING_STORE.dat";
	FILE *fp = fopen(fname, "r");
	FILE *ffp;
	char *chp;
	int val;
	int numRead;
	
	if (fp == NULL) {
		printf("ERROR: cannot open file %s for reading. \n", fname);
		exit(8);
	}	
	
	ffp = fopen(infile, "r");
	if (ffp == NULL) {
		fprintf(stderr, "cannnot read file '%s' \n", infile);
		return(8);
	}
	
	numRead = 0;
	chp = fgets(buffer, BUFLEN, ffp);
	
	while (numRead < 1000 && chp != NULL) {
		buffer[strlen(buffer)-1] = '\0';
		val = atoi(buffer);
		decodeAddress(val, &pageNumber, &pageOffset);
		readFromBackingStore(&fp, &buffer2, pageNumber);
		int value = (int)buffer2[(int)pageOffset];
		chp = fgets(buffer, BUFLEN, ffp);
		int physicalAddress = numRead * PAGE_SIZE + (int)pageOffset;
		printf("Virtual address: %i (%i, %i) Physical address: %i (%i, %i) Value: %i \n", 
		val, (int)pageNumber, (int)pageOffset, physicalAddress, numRead, (int)pageOffset, value);
		++numRead;
	}
	
	fclose(fp);
	fclose(ffp);
	
	return 0;	
}