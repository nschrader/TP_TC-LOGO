/**
 * @file
 * This a very easy implementation that helps detecting memory leaks.
 * It cannot tell where they occur, but at least if they occur,
 * and is designed to be used with CUnit.
 */

#ifndef MEMORY_LEAK_H
#define MEMORY_LEAK_H

/**
 * @struct MemoryRecord
 * A simply linked-list to keep track of allocations and frees.
 *
 * @var MemoryRecord::p
 * Pointer to the allocatated memory
 * @var MemoryRecord::s
 * Size of the allocatated memory
 * @var MemoryRecord::next
 * Pointer to the next @ref MemoryRecord element in list
 */
typedef struct _MemoryRecord {
  void* p;
  size_t s;
  struct _MemoryRecord *next;
} MemoryRecord;

/**
 * Replacement function for free()
 */
void memoryLeak_free(const void* p);

/**
 * Replacement function for malloc()
 */
void* memoryLeak_malloc(size_t s);

/**
 * Check if there where any memory leaks and clean-up leak checker
 *
 * @returns 1 if there were, 0 if not
 */
int memoryLeak_close();

/**
 * Custom assert macro to test for memory leaks
 */
#define ASSERT_MEMORY_LEAKS() { if (memoryLeak_close()) \
  CU_FAIL("Detected memory leek. Debug with Valgrind!") }

/**
 * To keep track of allocations and frees, we have to replace
 * those functions with ours and check them afterwards.
 * Define "NO_MEMORY_LEAKER" if you want to disable this
 * feature for example for Valgrind debugging.
 */
#define MEMORY_LEAKER
#ifndef NO_MEMORY_LEAKER

#define free(x) memoryLeak_free(x) //!< See @ref MEMORY_LEAKER
#define malloc(x) memoryLeak_malloc(x) //!< See @ref MEMORY_LEAKER

#endif

#endif
