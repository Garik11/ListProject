#include <stdio.h>
#include "./src/List.h"

int main(void)
{
    List *ls = ListCtor(10, 10);
    size_t poses[5];
    // ListPushFront(ls, 10, &nome);
    ListPushFront   (ls, 11, &poses[0]);
    ListPushFront   (ls, 12, &poses[1]);
    ListPushBack    (ls, 13, &poses[2]);
    ListInsert      (ls, 14, 1, &poses[3]);
    ListPushBack    (ls, 15, &poses[4]);

    LIST_DUMP(ls, LIST_ALL_OK);
    ListDelete(ls, 5);
    ListDelete(ls, 3);
    LIST_DUMP(ls, LIST_ALL_OK);

    *ListAt(ls, poses[1]) = 555;
    *ListAt(ls, 1) = 666;
    *ListAt(ls, poses[3]) = 777;
    *ListAt(ls, poses[4]) = 888;

    ListShrinkToFit(ls);
    
    ListDtor(ls);
}

/*
List *ls = ListCtor(10);

size_t nome = {};
 ListPushBack(ls, 1, &nome);
 ListPushBack(ls, 2, &nome);
 ListPushBack(ls, 3, &nome);
 ListPushBack(ls, 4, &nome);
LIST_DUMP(ls, LIST_ALL_OK);
 //ListPushBack(ls, 5, &nome);
 ListShrinkToFit(ls);
 LIST_DUMP(ls, LIST_ALL_OK);
ListDtor(ls);
*/
/*
    List *ls = ListCtor(11);

    size_t nome = {};
     ListPushFront(ls, 1, &nome);
     ListPushFront(ls, 2, &nome);
     ListPushFront(ls, 3, &nome);
     ListPushFront(ls, 4, &nome);
     ListPushFront(ls, 5, &nome);
     ListPushFront(ls, 6, &nome);
     ListPushFront(ls, 7, &nome);
    ListPushFront(ls, 8, &nome);
    ListPushFront(ls, 9, &nome);
    ListShrinkToFit(ls);
     LIST_DUMP(ls, LIST_ALL_OK);
    ListDtor(ls);
*/

/*
List *ls = ListCtor(10);
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
ListDelete(ls, 3);
//ListDelete(ls, 3);
LIST_DUMP(ls, LIST_ALL_OK);
//*ListAt(ls, 2) = 666;
//LIST_DUMP(ls, LIST_ALL_OK);
//ListAdd(ls, 13, &nome);
//LIST_DUMP(ls, LIST_ALL_OK);
ListShrinkToFit(ls);
//LIST_DUMP(ls, LIST_ALL_OK);
ListDtor(ls);
*/