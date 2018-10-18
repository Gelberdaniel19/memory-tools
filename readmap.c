#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "readmap.h"

int getheap(int pid, long* regionstart, long* regionend) {
  // Make string for the path to maps
  char filename[128];
  snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);

  // Try to open the file
  FILE* maps;
  if ((maps = fopen(filename, "r")) == 0) {
    printf("Could not open file %s\n", filename);
    return 0;
  }

  // Create a line pointer and attempt to read a line
  char* lineptr = NULL;
  size_t len = 0;
  ssize_t readlen;
  int found = 0;
  while ((readlen = getline(&lineptr, &len, maps)) != -1) {
    if (strstr(lineptr, "[heap]") != NULL) {
      found = 1;
      break;
    }
  }

  // Return false if not found
  if (found == 0) {
    free(lineptr);
    fclose(maps);
    return 0;
  }

  // This is the hard part - Parse the line.
  // Get the memory addresses as char arrays
  char *addr1, *addr2;
  addr1 = strtok(lineptr, " -");
  addr2 = strtok(NULL, " -");
  *regionstart = (long)strtol(addr1, NULL, 16);
  *regionend = (long)strtol(addr2, NULL, 16);
  
  // Success, so free memory and return true
  free(lineptr);
  fclose(maps);
  return 1;  
}
