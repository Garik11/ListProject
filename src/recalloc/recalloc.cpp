#include "recalloc.h"

void* recalloc(void* ptr, size_t nmemd, size_t size, size_t old_nmemd, size_t old_size){
    void* new_ptr = realloc(ptr, nmemd * size);
    if(new_ptr == NULL)
        return NULL;
    size_t offset       = nmemd       * size;
    size_t offset_old   = old_nmemd   * old_size;
    if(offset > offset_old)
        memset((BYTE*)new_ptr + offset_old, 0, offset - offset_old);
    return new_ptr;
}