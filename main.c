#include "vmm1.latrembl.c"


int main() {
	int address = 0;
	int *pageNumber =0;
	int *pageOffset =0;
	unsigned char buffer[BUFLEN];
	unsigned char buffer2[BUFLEN];
	char *infile = "addresses.txt";
	
	char *fname = "BACKING_STORE.dat";
	FILE *fp = fopen(fname, "r");
	if (fp == NULL) {
		printf("ERROR: cannot open file %s for reading. \n", fname);
		exit(8);
	}
	
	FILE *ffp;
	char *chp;
	int val;
	int numRead;
	
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
		int physicalAddress = numRead * 256 + (int)pageOffset;
		printf("Virtual address: %i (%i, %i) Physical address: %i (%i, %i) Value: %i \n", 
		val, (int)pageNumber, (int)pageOffset, physicalAddress, numRead, (int)pageOffset, value);
		++numRead;
	}
	
	fclose(fp);
	fclose(ffp);
	
	return 0;	
}

