#ifndef _STRUCTSH_
#define _STRUCTSH_

struct Region {
  long start;
  long end;
};

struct I8Address {
  long addr;
  char value;
};
struct I16Address {
  long addr;
  short value;
};
struct I32Address {
  long addr;
  int value;
};
struct I64Address {
  long addr;
  long value;
};
struct FloatAddress {
  long addr;
  float value;
};
struct DoubleAddress {
  long addr;
  float value;
};

#endif
