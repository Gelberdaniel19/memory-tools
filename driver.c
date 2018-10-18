#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "readmap.h"

#define PID 4314            // Default PID to scan from
#define BUFSIZE 4096        // Buffer size when reading from mem

int scanInt32(pid_t pid, long regionstart, long regionend, int** results, int* size)
{
  // Initial memory allocation to allow reallocation later.
  *results = malloc(4);
  
  // Set up for reading from mem file
  char memstring[64];
  printf(memstring, sizeof(memstring), "/proc/%d/mem", pid);
  char buf[BUFSIZE];
  int fd = open(memstring, O_RDONLY);
  if (ptrace(PTRACE_ATTACH, pid, NULL, NULL) == -1) {
    printf("Could not read mem\n");
    return 0;
  }
  waitpid(pid, NULL, 0);

  // Read memory from file
  long offset = regionstart;
  *size = 0;
  int valuesfilled = 0;
  while (offset < regionend) {
    pread(fd, buf, sizeof(buf), offset);
    // Allocate more space in the array so that the buffer's bytes fit   
    *results = realloc(*results, BUFSIZE+(*size*sizeof(int)));
    if (*results == NULL) {
      printf("Error reallocating memory");
      return 0;
    }
    *size += BUFSIZE / sizeof(int);
    for (int i = 0; i < BUFSIZE; i += sizeof(int)) {
      int value = buf[i] | ((int)buf[i+1] << 8) | ((int)buf[i+2] << 16) | ((int)buf[i+3] << 24);
      (*results)[valuesfilled] = value;
      valuesfilled += 1;
    }
    offset += BUFSIZE;
  }

  // Wrap up
  *size = valuesfilled;
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return 1;
}

int main()
{
  // Get the start and end regions of the heap
  long regionstart, regionend;
  if (getheap(PID, &regionstart, &regionend) == 1) {
    printf("%ld-%ld\n", regionstart, regionend);
  }

  // Get the int values in that region
  int* results;
  int size;
  if (scanInt32(PID, regionstart, regionend, &results, &size) == 0)
    printf("Counldn't get the ints\n");
  
  printf("Region: %ld<->%ld\n", regionstart, regionend);
  printf("Values found: %d\n", size);
  return 0;
}
