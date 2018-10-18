#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

#include "readmap.h"

#define PID 5339
#define BUFSIZE 4096

int main()
{
  // Get the start and end regions of the heap
  long regionstart, regionend;
  if (getheap(PID, &regionstart, &regionend) == 1) {
    printf("%ld-%ld\n", regionstart, regionend);
  }

  // Set up for reading from mem file
  pid_t pid = PID;
  char memstring[128];
  snprintf(memstring, sizeof(memstring), "/proc/%d/mem", PID);
  char buf[BUFSIZE];
  int fd = open(memstring, O_RDWR);
  long attached = ptrace(PTRACE_ATTACH, pid, NULL, NULL);
  waitpid(PID, NULL, 0);

  // Read from mem file
  long offset = regionstart;
  while (offset < regionend) {
    pread(fd, buf, sizeof(buf), offset);
    for (int i = 0; i < BUFSIZE; i+=sizeof(int)) {
      if (buf[i] == 0 && buf[i+1] == 0 && buf[i+2] == 0 && buf[i+3] == 0)
	continue;
      int value = buf[i] | ( (int)buf[i+1] << 8 ) | ( (int)buf[i+2] << 16 ) | ( (int)buf[i+3] << 24 );
      if (value == 72)
	printf("%d %d %d %d\t%d\t%ld\n", buf[i], buf[i+1], buf[i+2], buf[i+3], value, offset+i);
    }
    offset += BUFSIZE;
  }

  // Wrap up
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
}

