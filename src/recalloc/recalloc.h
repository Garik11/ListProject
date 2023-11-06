#ifndef RECALLOC_H
#define RECALLOC_H
#include <malloc.h>
#include <string.h>

typedef char BYTE;

void* recalloc(void* ptr, size_t nmemd, size_t size, size_t old_nmemd, size_t old_size);

#endif // !RECALLOC_H