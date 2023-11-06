#include "List.h"

List *ListCtor(const size_t initial_size)
{

    assert(initial_size > 0);

    List* ls = (List*)calloc(1, sizeof(List));
    assert(ls != NULL);

    ls->size = initial_size;
    ls->number_of_elements = 0;

    ls->data = (Elem_t*)calloc(ls->size, sizeof(Elem_t));
    assert(ls->data != NULL);

    ls->next = (size_t*)calloc(ls->size, sizeof(size_t));
    assert(ls->next != NULL);

    ls->head = 0;
    ls->tail = 1;
    ls->free = 1;
    
    for(size_t i = 1; i < ls->size - 1; i++)
        ls->next[i] = i + 1;
    for(size_t i = 0; i < ls->size; i++)
        ls->data[i] = LIST_ELEM_POISON;

    return ls;
}

ListErrors ListDtor(List *ls)
{
    assert(ls       != NULL);
    assert(ls->data != NULL);
    assert(ls->next != NULL);

    free(ls->data   );
    free(ls->next   );
    free(ls         );

    return ListErrors();
}

ListErrors ListVerificator(const List *ls)
{

    ListErrors outputerrors = LIST_ALL_OK;

    if(ls == NULL)
        outputerrors |= LIST_BAD_POINTER;
    else {
        if(ls->data == NULL)
            outputerrors |= LIST_BAD_POINTER_DATA;
        if(ls->next == NULL)
            outputerrors |= LIST_BAD_POINTER_NEXT;
        #warning add check next add graphic
    }
    return outputerrors;
}

void ListDump(
                const List *ls          , 
                ListErrors errors       , 
                const char *LIST_NAME   , 
                const char *FILE_NAME   , 
                const int LINE          , 
                const char *FUNC
            )
{
    printf(SWORDSKUL);
    errors |= ListVerificator(ls);

    const char* lname = (LIST_NAME  == NULL) ? "???" : LIST_NAME    ;
    const char* fname = (FILE_NAME  == NULL) ? "???" : FILE_NAME    ;
    const char* func =  (FUNC       == NULL) ? "???" : FUNC         ;

    printf("List[%p] \"%s\" called from file:%s(%d) func:%s\n", ls, lname, fname, LINE, func);

    if(errors & LIST_BAD_POINTER)
        return;

    printf("\t{size = %lu\n", ls->size);
    printf("\t free = %lu\n", ls->free);
    printf("\t head = %lu\n", ls->head);
    printf("\t tail = %lu\n", ls->tail);
    printf("\t{number_of_elements = %lu\n", ls->number_of_elements);

    if(errors & (LIST_BAD_POINTER_DATA | LIST_BAD_POINTER_NEXT)){
        printf("\t data[error]\n"),
        printf("\t naxt[error]\n");
    }
    else{
        printf("\t data[%p]\n", ls->data);

        printf("\t\t{ ");
        for(size_t pos = 0; pos < ls->size; pos++)
            printf("%" LISTELEMSPECLENGTH LISTELEMSPEC " ", ls->data[pos]);
        printf(" }\n");

        printf("\t next[%p]\n", ls->next);

        printf("\t\t{ ");
        for(size_t pos = 0; pos < ls->size; pos++)
            printf("%" LISTELEMSPECLENGTH "lu" " ", ls->next[pos]);
        printf(" }\n");
    }
    printf("\t}\n");
}

ListErrors ListPushBack(List *ls, const Elem_t value, size_t *added_pos){
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    assert(added_pos != NULL);

    ls->data[ls->free] = value;
    size_t next = ls->next[ls->free];
    ls->next[ls->tail] = ls->free;
    ls->next[ls->free] = 0;
    ls->tail = ls->free;
    *added_pos = ls->free;
    ls->free = next;

    ls->number_of_elements++;
    return errors;
}

ListErrors ListPushFront(List *ls, const Elem_t value, size_t *added_pos){
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    assert(added_pos != NULL);

    ls->data[ls->free] = value;
    size_t next = ls->next[ls->free];
    ls->next[ls->free] = ls->head;
    ls->head = ls->free;
    *added_pos = ls->free;
    ls->free = next;

    ls->number_of_elements++;
    return errors;
}

ListErrors ListInsert(List *ls, const Elem_t value, size_t where_to_insert, size_t *added_pos)
{
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    assert(added_pos != NULL);

    ls->data[ls->free] = value;
    size_t next = ls->next[ls->free];
    ls->next[ls->free] = ls->next[where_to_insert];
    ls->next[where_to_insert] = ls->free;
    *added_pos = ls->free;
    ls->free = next;
    
    ls->number_of_elements++;
    return errors;
}

ListErrors ListPopFront(List *ls){
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    ls->data[ls->head] = LIST_ELEM_POISON;
    size_t next = ls->next[ls->head];
    ls->next[ls->head] = ls->free;
    ls->free = ls->head;
    ls->head = next;

    ls->number_of_elements--;
    return errors;
}

ListErrors ListPopBack(List *ls, size_t element_before_delete){
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    size_t where_to_delete = ls->next[element_before_delete];
    printf("element_before_delete = %lu\n", element_before_delete);
    printf("where_to_delete = %lu\n", where_to_delete);
    size_t next = ls->next[where_to_delete];
    ls->data[where_to_delete] = LIST_ELEM_POISON;
    ls->next[where_to_delete] = ls->free;
    ls->free = where_to_delete;
    ls->next[element_before_delete] = next;
    ls->tail = element_before_delete;

    ls->number_of_elements--;
    return errors;
}

ListErrors ListDelete(List *ls, size_t element_before_delete)
{
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    size_t where_to_delete = ls->next[element_before_delete];
    printf("element_before_delete = %lu\n", element_before_delete);
    printf("where_to_delete = %lu\n", where_to_delete);
    size_t next = ls->next[where_to_delete];
    ls->data[where_to_delete] = LIST_ELEM_POISON;
    ls->next[where_to_delete] = ls->free;
    ls->free = where_to_delete;
    ls->next[element_before_delete] = next;

    ls->number_of_elements--;
    return errors;
}

Elem_t* ListAt(const List* ls, const size_t pos)
{
    assert(pos != 0);
    assert(pos < ls->size);
    assert(ls->data[pos] != LIST_ELEM_POISON);
    return ls->data + pos;
}