#include <sys/types.h>

#include "structs.h"

int scanInt8(pid_t pid, struct Region region, struct I8Address** results, int* size);
int scanInt16(pid_t pid, struct Region region, struct I16Address** results, int* size);
int scanInt32(pid_t pid, struct Region region, struct I32Address** results, int* size);
int scanInt64(pid_t pid, struct Region region, struct I64Address** results, int* size);
