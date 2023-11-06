#include "List.h"

List *ListCtor(const Elem_t initial_value, const size_t initial_size)
{
    assert(initial_size > 0);

    List* ls = (List*)calloc(1, sizeof(List));
    assert(ls != NULL);

    ls->size = initial_size;
    ls->number_of_elements = 1;

    ls->data = (Elem_t*)calloc(ls->size, sizeof(Elem_t));
    assert(ls->data != NULL);

    ls->next = (size_t*)calloc(ls->size, sizeof(size_t));
    assert(ls->next != NULL);

    ls->head = 1;
    ls->tail = 1;
    ls->free = 2;
    
    for(size_t pos = 1; pos < ls->size - 1; pos++)
        ls->next[pos] = pos + 1;
    for(size_t pos = 0; pos < ls->size; pos++)
        ls->data[pos] = LIST_ELEM_POISON;

    printf("INIT VALUE: %ld\n", initial_value);
    ls->next[1] = 0;
    ls->data[1] = initial_value;

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
        #warning add others checks
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

    printf("List[%p] \"%s\" called from file:%s(%d) " PURPLEBACKGROUND("func:%s") "\n", ls, lname, fname, LINE, func);

    if(errors & LIST_BAD_POINTER)
        return;

    printf("\t{size = %lu\n", ls->size);
    printf("\t free = %lu\n", ls->free);
    printf("\t head = %lu\n", ls->head);
    printf("\t tail = %lu\n", ls->tail);
    printf("\t number_of_elements = %lu\n", ls->number_of_elements);

    if(errors & (LIST_BAD_POINTER_DATA | LIST_BAD_POINTER_NEXT)){
        printf("\t data[error]\n"),
        printf("\t naxt[error]\n");
    }
    else{
        printf("\t data[%p]\n", ls->data);

        printf("\t\t{ ");
        for(size_t pos = 0; pos < ls->size; pos++){
            if(ls->data[pos] != LIST_ELEM_POISON)
                printf("%" LISTELEMSPECLENGTH LISTELEMSPEC " ", ls->data[pos]);
            else
                printf("%s%"LISTELEMSPECLENGTH"s%s ", GREENOPEN, "POISON", GREENCLOSE);
        }
        printf(" }\n");

        printf("\t next[%p]\n", ls->next);

        printf("\t\t{ ");
        for(size_t pos = 0; pos < ls->size; pos++)
            if(ls->next[pos] != LIST_ELEM_POISON)
                printf("%" LISTELEMSPECLENGTH "lu"" ", ls->next[pos]);
            else
                printf("%s%"LISTELEMSPECLENGTH"s%s ", PURPLEOPEN, "POISON", PURPLECLOSE);
        printf(" }\n");

        printf("\t\t  ");
        for(size_t pos = 0; pos < ls->size; pos++){
            static const char *out;
            if(pos == ls->free){
                printf(LIGHTGREENOPEN);
                out = LIST_DUMP_FREE;
            }
            else if(pos == ls->head){
                printf(LIGHTBLUEOPEN);
                out = LIST_DUMP_HEAD;
            }
            else if(pos == ls->tail){
                printf(LIGHTREDOPEN);
                out = LIST_DUMP_TAIL;
            }
            else
                out = LIST_DUMP_EMPT;
            printf("%"LISTELEMSPECLENGTH "s ", out);
            printf(COLORCLOSE);
        }
        printf("\n");
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
    size_t next = ls->next[where_to_delete];
    ls->data[where_to_delete] = LIST_ELEM_POISON;
    ls->next[where_to_delete] = ls->free;
    ls->free = where_to_delete;
    ls->next[element_before_delete] = next;

    ls->number_of_elements--;
    return errors;
}

ListErrors ListSizeMultiplyer(List *ls, size_t multiplier)
{   
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    void* newdata = recalloc(
                                ls->data, 
                                ls->size * multiplier, 
                                sizeof(Elem_t), 
                                ls->size, 
                                sizeof(Elem_t)
                            );
    assert(newdata != NULL);
    ls->data = (Elem_t*)newdata;

    void* newnext = recalloc(
                                ls->next, 
                                ls->size * multiplier, 
                                sizeof(size_t), 
                                ls->size, 
                                sizeof(size_t)
                            );
    assert(newnext != NULL);
    ls->next = (size_t*)newnext;

    for(size_t pos = ls->size; pos < ls->size * multiplier - 1; pos++)
        ls->next[pos] = pos + 1;
    ls->next[ls->size * multiplier - 1] = ls->free;
    ls->free = ls->size;
    for(size_t pos = ls->size; pos < ls->size * multiplier; pos ++)
        ls->data[pos] = LIST_ELEM_POISON;
    ls->size *= multiplier;

    return errors;
}


static size_t ListFindPos(const List *ls, size_t elpos){
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    size_t pos = ls->head;
    while(ls->next[pos] != elpos && pos != 0)
        pos = ls->next[pos];

    return pos;
}

ListErrors ListShrinkToFit(List *ls)
{
    ListErrors errors = ListVerificator(ls);

    assert(errors == LIST_ALL_OK);

    LIST_DUMP(ls, LIST_ALL_OK);

    /*put head first*/
    if(ls->head != 1){
        if(ls->data[1] == LIST_ELEM_POISON){ /*is free*/
            ls->data[1] = ls->data[ls->head];
            ls->next[1] = ls->next[ls->head];
            ls->data[ls->head] = LIST_ELEM_POISON;
            ls->next[ls->head] = LIST_POISON;
            ls->head = 1;
        }
        else{ /*isn't free*/
                if(ls->next[ls->head] != 1){/*checking whether the head refers to the first element*/
                    size_t element_before_phys_first = ListFindPos(ls, 1);
                    assert(element_before_phys_first != 0);
                    SWAP_T(Elem_t, ls->data[1], ls->data[ls->head]);
                    SWAP_T(size_t, ls->next[1], ls->next[ls->head]);
                    ls->next[element_before_phys_first] = ls->head;
                    if(ls->tail == 1)
                        ls->tail = ls->head;
                    ls->head = 1;
                }
                else {/*the head refers to the first element*/
                    SWAP_T(Elem_t, ls->data[1], ls->data[ls->head]);
                    SWAP_T(size_t, ls->next[1], ls->next[ls->head]);
                    ls->next[1] = ls->head;
                    if(ls->tail == 1)
                        ls->tail = ls->head;
                    ls->head = 1;

                }

            }
    }

    LIST_DUMP(ls, LIST_ALL_OK);
    size_t pos = ls->head;
    size_t next = ls->next[pos];
    #warning bug more tests are needed
    
    /*shring to fit element without head and tail*/
    /*searches for the first available free elements, 
    elements with POISON are considered free*/
    size_t next_free = 1;
    while(next != ls->tail && next != 0){

        for(; next_free < ls->size; next_free++){
            if(ls->data[next_free] == LIST_ELEM_POISON)
                break;
        }
        //LIST_DUMP(ls, LIST_ALL_OK);
        if(next_free == ls->size){
            break;
        }

        #warning more tests are needed
        /*We don't do sorting here, 
        so if an element lies before a free one, 
        it doesn't need to be moved*/
        while(next < next_free && next != 0){
            pos = next;
            next = ls->next[next];
        }
        #warning !!more tests are needed!!
        if(next == 0)
            break;
        //printf("pos = %lu\n", pos);
        //printf("next = %lu\n", next);
        //printf("new pos = %lu\n", next_free);
        //printf("old inf %lu %ld\n", ls->next[next], ls->data[next]);
        #warning more tests are needed
        ls->data[next_free] = ls->data[next];
        ls->next[next_free] = ls->next[next];
        assert(next != ls->tail);
        //if(next == ls->tail)
        //    ls->tail = next_free;
        ls->next[pos] = next_free;
        size_t nextcyc = ls->next[next];
        pos = next_free;
        ls->data[next] = LIST_ELEM_POISON;
        ls->next[next] = LIST_POISON;
        next = nextcyc;
        

    }
    //LIST_DUMP(ls, LIST_ALL_OK);

    /*put tail last*/
    printf("next_free = %lu\n", next_free);
    for(; next_free < ls->size; next_free++){
        if(ls->data[next_free] == LIST_ELEM_POISON)
            break;
    }
    #warning add error
    printf("next_free = %lu\n", next_free);
    //if(next_free == ls->size){
    //    return errors;
    //}
    printf("next_free = %lu\n", next_free);
    //
    //    pos = before ls->tail 
    //    next = ls->tail
    //
   //assert(pos != ls->tail);
   assert(pos != 0);

    if(ls->tail > next_free){
        ls->next[pos] = next_free;
        ls->data[next_free] = ls->data[ls->tail];
        ls->next[next_free] = ls->next[ls->tail];
        ls->data[ls->tail] = LIST_ELEM_POISON;
        ls->next[ls->tail] = LIST_POISON;
        ls->tail = next_free;
    }
    /*We cut the array completely, there will be no free elements*/
    ls->free = 0;
    #warning Remove the magic number
    void* newdata = recalloc(
                                ls->data, 
                                ls->number_of_elements + 1, 
                                sizeof(Elem_t), 
                                ls->size, 
                                sizeof(Elem_t)
                            );
    assert(newdata != NULL);
    ls->data = (Elem_t*)newdata;

    void* newnext = recalloc(
                                ls->next, 
                                ls->number_of_elements + 1, 
                                sizeof(size_t), 
                                ls->size, 
                                sizeof(size_t)
                            );
    assert(newnext != NULL);
    ls->next = (size_t*)newnext;

    ls->size = ls->number_of_elements + 1;

    LIST_DUMP(ls, LIST_ALL_OK);

    return errors;
}

Elem_t* ListAt(const List* ls, const size_t pos)
{
    assert(pos != 0);
    assert(pos < ls->size);
    assert(ls->data[pos] != LIST_ELEM_POISON);
    return ls->data + pos;
}