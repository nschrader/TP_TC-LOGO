#ifndef MEMORY_LEAK_H
#define MEMORY_LEAK_H

typedef struct _MemoryRecord {
  void* p;
  size_t s;
  struct _MemoryRecord *next;
} MemoryRecord;

void memoryLeak_free(const void* p);
void* memoryLeak_malloc(size_t s);
int memoryLeak_close();

/*
 * To keep track of allocations and frees, we have to replace
 * those functions with ours and check them afterwards.
 * Uncomment the follwoing define if you want to disable this
 * feature for example for Valgrind debugging.
 */
//#define NO_MEMORY_LEAKER
#ifndef NO_MEMORY_LEAKER
#define free(x) memoryLeak_free(x)
#define malloc(x) memoryLeak_malloc(x);
#endif

#endif
