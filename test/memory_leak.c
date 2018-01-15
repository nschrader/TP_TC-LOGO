#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <CUnit/Basic.h>

#define NO_MEMORY_LEAKER
#include "memory_leak.h"

#define ASSERT_HERE() assert(1);

static MemoryRecord* memoryRecord = NULL;

static MemoryRecord *do_memoryLeak_free(MemoryRecord* record, void* p) {
  if (record == NULL) {
    return NULL;
  }
  if (record->p == p) {
    MemoryRecord* nextRecord = record->next;
    free(record->p);
    free(record);
    return nextRecord;
  }
  record->next = do_memoryLeak_free(record->next, p);
  return record;
}

void memoryLeak_free(void* p) {
  if (memoryRecord == NULL) {
    fprintf(stderr, "Attempting to free invalid address. Debug with Valgrind!");
    ASSERT_HERE();
  }
  memoryRecord = do_memoryLeak_free(memoryRecord, p);
}

static MemoryRecord* do_memoryLeak_malloc(size_t s) {
  MemoryRecord* record = malloc(sizeof(MemoryRecord));
  record->p = malloc(s);
  record->next = NULL;
  return record;
}

void* memoryLeak_malloc(size_t s) {
  if (memoryRecord == NULL) {
    memoryRecord = do_memoryLeak_malloc(s);
    return memoryRecord->p;
  } else {
    MemoryRecord* record = memoryRecord;
    while (record->next != NULL) {
      record = record->next;
    }
    record->next = do_memoryLeak_malloc(s);
    return record->next->p;
  }
}

static void do_memoryLeak_close(MemoryRecord* record) {
  if (record != NULL) {
    do_memoryLeak_close(record->next);
    free(record->p);
    free(record);
  }
}

int memoryLeak_close() {
  int hasMemoryLeak = (memoryRecord != NULL);
  do_memoryLeak_close(memoryRecord);
  memoryRecord = NULL;
  return hasMemoryLeak;
}

void* real_malloc(size_t n) {
  return malloc(n);
}

void real_free(void* p) {
  free(p);
}
