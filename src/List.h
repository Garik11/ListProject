#ifndef LIST_H
#define LIST_H

#include <stddef.h>
#include <stdint.h>

#include <malloc.h>
#include <assert.h>

#include "recalloc/recalloc.h"

#include "skul.h"
#include "colors.h"

#define LIST_DUMP(ls, errors) ListDump(ls, errors, #ls, __FILE__, __LINE__, __func__)
#define SWAP_T(T, a, b) \
    do                  \
    {                   \
        T temp = a;     \
        a = b;          \
        b = temp;       \
    } while (0)

typedef uint64_t ListErrors;
typedef int64_t Elem_t;

/*for dump*/
#define LISTELEMSPEC "ld"
#define LISTELEMSPECLENGTH "10"
/*the number of elements must match LISTELEMSPECLENGTH including \0*/
static const char *const LIST_DUMP_FREE = "fffffffff";
static const char *const LIST_DUMP_HEAD = "hhhhhhhhh";
static const char *const LIST_DUMP_TAIL = "ttttttttt";
static const char *const LIST_DUMP_EMPT = "         ";

static const size_t LIST_STANDART_INITIAL_SIZE  = 15;
static const size_t LIST_STANDART_MULTIPLIER    = 2 ;

static const int64_t    LIST_POISON         = 0xDEADBABE                        ;
static const Elem_t     LIST_ELEM_POISON    = *(const Elem_t *)(&LIST_POISON)   ;

struct List
{

    size_t size;
    size_t number_of_elements;

    Elem_t *data;
    size_t *next;

    size_t free;
    size_t head;
    size_t tail;

};

List *ListCtor(const Elem_t initial_value, const size_t initial_size = LIST_STANDART_INITIAL_SIZE);

ListErrors ListDtor(List *ls);

ListErrors ListVerificator(const List *ls);

void ListDump(
                const List* ls          ,
                ListErrors  errors      ,
                const char* LIST_NAME   ,
                const char* FILE_NAME   ,
                const int   LINE        ,
                const char* FUNC
            );

ListErrors ListPushBack (List *ls, const Elem_t value, size_t *added_pos);
ListErrors ListPushFront(List *ls, const Elem_t value, size_t *added_pos);
/*Adds an element after where_to_insert
where_to_insert must be non-zero and not equal to tail
Otherwise, use PushFront and PushBack respectively!(or UB)*/
ListErrors ListInsert(List *ls, const Elem_t value, size_t where_to_insert, size_t *added_pos);

ListErrors ListPopFront (List *ls);
/*For optimization, you had to keep the element number preceding the tail.
If you have lost it, write the search function, 
the author is not responsible for the slowness of such a program*/
ListErrors ListPopBack  (List *ls, size_t element_before_delete);

/*element_before_delete must be non-zero and not equal to tail
Otherwise, use PopFront and PopBack respectively!*/
ListErrors ListDelete(List *ls, size_t element_before_delete);

/*Increases the data size by the specified number of times, by the standard twice*/
ListErrors ListSizeMultiplyer   (List *ls, size_t multiplier = LIST_STANDART_MULTIPLIER);
/*Puts head in the first place and tail in the last, replaces free elements between them.
!WARNING:Your numbers and your pointers will NO be verified.
All free elements disappear, an attempt to add will result in UB*/
ListErrors ListShrinkToFit      (List *ls);

Elem_t *ListAt(const List *ls, const size_t pos);

enum LISTERRORS
{
    LIST_ALL_OK             = 0 << 0,
    LIST_BAD_POINTER        = 1 << 0,
    LIST_BAD_POINTER_DATA   = 1 << 1,
    LIST_BAD_POINTER_NEXT   = 1 << 2,
    LIST_BAD_INCORRECT_NEXT = 1 << 3,
    LIST_BAD_ELEMENT_NUMBER = 1 << 4
};

#endif // !LIST_H