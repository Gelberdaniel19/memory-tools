#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "readmap.h"

int getRegions(int pid, struct Region** regions, int* size) {
  // Size starts at zero, and initialize region
  *size = 0;
  *regions = malloc(sizeof(struct Region));

  // Make string for the path to maps
  char filename[128];
  snprintf(filename, sizeof(filename), "/proc/%d/maps", pid);

  // Try to open the file
  FILE* maps;
  if ((maps = fopen(filename, "r")) == 0) {
    printf("Could not open file %s\n", filename);
    return 0;
  }

  // Create a line pointer and attempt to read all lines
  char* lineptr = NULL;
  size_t len = 0;
  ssize_t readlen;
  int found = 0;
  while ((readlen = getline(&lineptr, &len, maps)) != -1) {
    // Parse all the lins for the addresses
    *regions = realloc(*regions, (*size + 1) * sizeof(struct Region));
    char *addr1, *addr2;
    addr1 = strtok(lineptr, " -");
    addr2 = strtok(NULL, " -");
    ((*regions)+*size)->start = (long)strtol(addr1, NULL, 16);
    ((*regions)+*size)->end = (long)strtol(addr2, NULL, 16);
    *size += 1;
  }
  
  // Success, wrap up
  free(lineptr);
  fclose(maps);
  return 1;  
}
