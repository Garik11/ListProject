#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>

#include <malloc.h>
#include <assert.h>

#include "skul.h"

#define LIST_DUMP(ls, errors) ListDump(ls, errors, #ls, __FILE__, __LINE__, __func__)

typedef uint64_t    ListErrors  ;
typedef int64_t     Elem_t      ;
#define LISTELEMSPEC        "ld"
#define LISTELEMSPECLENGTH  "10"
static const size_t standart_list_initial_size = 15;

static const int64_t LIST_POISON = 0xDEADBABE;
static const Elem_t  LIST_ELEM_POISON = *(Elem_t*)(&LIST_POISON);

struct List{
    size_t size;
    size_t number_of_elements;
    Elem_t *data;
    size_t* next;
    size_t free;
    size_t head;
    size_t tail;
};

List*       ListCtor            (const size_t initial_size = standart_list_initial_size);

ListErrors  ListDtor            (List* ls);

ListErrors  ListVerificator     (const List* ls);

void        ListDump            (
                                    const List* ls          , 
                                    ListErrors errors       , 
                                    const char* LIST_NAME   , 
                                    const char* FILE_NAME   , 
                                    const int LINE          , 
                                    const char* FUNC
                                );

ListErrors ListPushBack(List *ls, const Elem_t value, size_t *added_pos);
ListErrors ListPushFront(List *ls, const Elem_t value, size_t *added_pos);
/*where_to_insert must be non-zero and not equal to tail
Otherwise, use PushFront and PushBack respectively!*/
ListErrors ListInsert(List *ls, const Elem_t value, size_t where_to_insert, size_t *added_pos);

ListErrors ListPopFront(List *ls);
ListErrors ListPopBack(List *ls, size_t element_before_delete);
/*element_before_delete must be non-zero and not equal to tail
Otherwise, use PushFront and PushBack respectively!*/
ListErrors ListDelete(List *ls, size_t element_before_delete);

ListErrors  ListShrinkToFit (List* ls);

Elem_t* ListAt(const List* ls, const size_t pos);

enum LISTERRORS{
    LIST_ALL_OK                 = 0 << 0,
    LIST_BAD_POINTER            = 1 << 0,
    LIST_BAD_POINTER_DATA       = 1 << 1,
    LIST_BAD_POINTER_NEXT       = 1 << 2,
    LIST_BAD_INCORRECT_NEXT     = 1 << 3,
    LIST_BAD_ELEMENT_NUMBER     = 1 << 4
};

#endif // !LIST_H