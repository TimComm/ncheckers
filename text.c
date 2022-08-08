#include <stdio.h>

#include "text.h"

void readCheckersA()
{
  char buffer[20]; // Buffer to store data
  FILE * stream;
  stream = fopen("txt1.txt", "r");
  int count = fread(&buffer, sizeof(char), 20, stream);
  fclose(stream);
  // Printing data to check validity
  printf("Data read from file: %s \n", buffer);
  printf("Elements read: %d", count);
}
