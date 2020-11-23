#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#define BUFLEN 256

int decodeAddress(int address, int *pageNumber, int *pageOffset) {
	//printf("\nDecoding Address %i...\n", address);
	if (address > 65535 || address < 0) {
		printf("ERROR: Address not in range. \n");
		return -1;
	} else {
		*pageNumber = address / 256;
		*pageOffset = address % 256;
		
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
		
	offset = 256 * pageNumber;		
	
	rtnval = fseek(*fp, offset, 0);	
	//printf("Inside readFromBackingStore() --- Seek return value: %i \n", rtnval);
	
	if (rtnval != 0) {
		printf("File Seek Failed! \n");
		return (rtnval);
	}	
	
	rtnval = fread(buffer, 1, 256, *fp);
	//printf("Inside readFromBackingStore() --- Read return value: %i \n", rtnval);
	
	if (rtnval != 256) {
		printf("Reading Failed! \n");
		return(1);
	}	else {		
		//printf("Reading Complete! \n");
		return(0);
	}	
}


