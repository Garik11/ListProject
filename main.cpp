#include <stdio.h>
#include "./src/List.h"

int main(void){
    List* ls = ListCtor(10);
    size_t mypos = {};
    size_t nome = {};
    size_t temp = {};
    ListPushFront(ls, 10, &nome);
    ListPushFront(ls, 11, &temp);
    ListPushFront(ls, 12, &nome);
    ListPushBack(ls, 13, &temp);
    ListInsert(ls, 14, 1, &mypos);
    ListPushBack(ls, 15, &temp);
    //ListInsert(ls, 13, 0, &nome);
    LIST_DUMP(ls, LIST_ALL_OK);
    ListDelete(ls, 5);
    LIST_DUMP(ls, LIST_ALL_OK);
    *ListAt(ls, 2) = 666;
    LIST_DUMP(ls, LIST_ALL_OK);
    //ListAdd(ls, 13, &nome);
    //LIST_DUMP(ls, LIST_ALL_OK);
    ListDtor(ls);
}