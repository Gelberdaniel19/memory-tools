#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "readmap.h"
#include "ptrace.h"

#define PID 3535            // Default PID to scan from

int main()
{
  // Get the start and end regions of the heap
  struct Region region;
  if (getheap(PID, &region) == 0) {
    printf("Could not find the heap");
    return 0;
  }

  // Get the int values in that region
  int* results;
  int size;
  if (scanInt32(PID, region, &results, &size) == 0) {
    printf("Counldn't get the ints\n");
    return 0;
  }

  for (int i = 0; i < size; i+=4)
    printf("%d\t%d\t%d\t%d\n", results[i], results[i+1], results[i+2], results[i+3]);
  
  printf("\nRegion: %ld<->%ld\n", region.start, region.end);
  printf("Values found: %d\n", size);
  return 0;
}
