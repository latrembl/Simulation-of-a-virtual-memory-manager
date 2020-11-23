#include <stdio.h>
#include <stdlib.h>

#define FILENAME "BACKING_STORE.dat"
#define BUFLEN 256 * 256

int main() {
  FILE *fp;
  unsigned char buffer[BUFLEN];
  long offset;
  int rtnval, i, value, numbytes;

  fp = (FILE *) fopen(FILENAME, "rb");
  if (fp == NULL) {
    printf("ERROR: cannot open file %s for reading\n", FILENAME);
    return 8;
  }

  // read 16 bytes from the file, starting at position 64

  // first seek to position 64
  offset = 0;
  rtnval = fseek(fp, offset, 0);
  if (rtnval != 0) {
    printf("ERROR from fseek()\n");
    fclose(fp);
    return 8;
  }

  numbytes = fread(buffer, 1, BUFLEN, fp);
  if (numbytes != BUFLEN) {
    printf("ERROR: could not read %d bytes\n", BUFLEN);
    fclose(fp);
    return 8;
  }

  printf("here's what I read:\n");
  for (i=0; i<BUFLEN; ++i) {
    int value = (int) buffer[i];
    printf("byte %d: %u\n", i, value);
  }

  fclose(fp);
  return 0;
}
