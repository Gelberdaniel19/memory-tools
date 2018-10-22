#include <stdio.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <unistd.h>

#include "ptrace.h"

#define BUFSIZE 4096

int scanInt8(pid_t pid, struct Region region, struct I8Address** results, int* size)
{
  // Initial memory allocation to allow reallocation later.
  *results = malloc(sizeof(struct I8Address));
  
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
  long offset = region.start;
  *size = 0;
  int valuesfilled = 0;
  while (offset < region.end) {
    pread(fd, buf, sizeof(buf), offset);
    // Allocate more space in the array so that the buffer's bytes fit
    *results = realloc(*results, (BUFSIZE / sizeof(char) * sizeof(struct I8Address)) + (*size * sizeof(struct I8Address)));
    if (*results == NULL) {
      printf("Error reallocating memory");
      return 0;
    }
    *size += BUFSIZE / sizeof(char);
    for (int i = 0; i < BUFSIZE; i += sizeof(char)) {
      char value = buf[i] | ((char)buf[i+1] << 8) | ((char)buf[i+2] << 16) | ((char)buf[i+3] << 24);
      ((*results)+valuesfilled)->value = value;
      ((*results)+valuesfilled)->addr = offset + i;
      valuesfilled += 1;
    }
    offset += BUFSIZE;
  }

  // Wrap up
  *size = valuesfilled;
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return 1;
}

int scanInt16(pid_t pid, struct Region region, struct I16Address** results, int* size)
{
  // Initial memory allocation to allow reallocation later.
  *results = malloc(sizeof(struct I16Address));
  
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
  long offset = region.start;
  *size = 0;
  int valuesfilled = 0;
  while (offset < region.end) {
    pread(fd, buf, sizeof(buf), offset);
    // Allocate more space in the array so that the buffer's bytes fit
    *results = realloc(*results, (BUFSIZE / sizeof(short) * sizeof(struct I16Address)) + (*size * sizeof(struct I16Address)));
    if (*results == NULL) {
      printf("Error reallocating memory");
      return 0;
    }
    *size += BUFSIZE / sizeof(short);
    for (int i = 0; i < BUFSIZE; i += sizeof(short)) {
      short value = buf[i] | ((short)buf[i+1] << 8) | ((short)buf[i+2] << 16) | ((short)buf[i+3] << 24);
      ((*results)+valuesfilled)->value = value;
      ((*results)+valuesfilled)->addr = offset + i;
      valuesfilled += 1;
    }
    offset += BUFSIZE;
  }

  // Wrap up
  *size = valuesfilled;
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return 1;
}

int scanInt32(pid_t pid, struct Region region, struct I32Address** results, int* size)
{
  // Initial memory allocation to allow reallocation later.
  *results = malloc(sizeof(struct I32Address));
  
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
  long offset = region.start;
  *size = 0;
  int valuesfilled = 0;
  while (offset < region.end) {
    pread(fd, buf, sizeof(buf), offset);
    // Allocate more space in the array so that the buffer's bytes fit
    *results = realloc(*results, (BUFSIZE / sizeof(int) * sizeof(struct I32Address)) + (*size * sizeof(struct I32Address)));
    if (*results == NULL) {
      printf("Error reallocating memory");
      return 0;
    }
    *size += BUFSIZE / sizeof(int);
    for (int i = 0; i < BUFSIZE; i += sizeof(int)) {
      int value = buf[i] | ((int)buf[i+1] << 8) | ((int)buf[i+2] << 16) | ((int)buf[i+3] << 24);
      ((*results)+valuesfilled)->value = value;
      ((*results)+valuesfilled)->addr = offset + i;
      valuesfilled += 1;
    }
    offset += BUFSIZE;
  }

  // Wrap up
  *size = valuesfilled;
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return 1;
}

int scanInt64(pid_t pid, struct Region region, struct I64Address** results, int* size)
{
  // Initial memory allocation to allow reallocation later.
  *results = malloc(sizeof(struct I64Address));
  
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
  long offset = region.start;
  *size = 0;
  int valuesfilled = 0;
  while (offset < region.end) {
    pread(fd, buf, sizeof(buf), offset);
    // Allocate more space in the array so that the buffer's bytes fit
    *results = realloc(*results, (BUFSIZE / sizeof(long) * sizeof(struct I64Address)) + (*size * sizeof(struct I64Address)));
    if (*results == NULL) {
      printf("Error reallocating memory");
      return 0;
    }
    *size += BUFSIZE / sizeof(long);
    for (int i = 0; i < BUFSIZE; i += sizeof(long)) {
      long value = buf[i] | ((long)buf[i+1] << 8) | ((long)buf[i+2] << 16) | ((long)buf[i+3] << 24);
      ((*results)+valuesfilled)->value = value;
      ((*results)+valuesfilled)->addr = offset + i;
      valuesfilled += 1;
    }
    offset += BUFSIZE;
  }

  // Wrap up
  *size = valuesfilled;
  ptrace(PTRACE_DETACH, pid, NULL, NULL);
  return 1;
}
