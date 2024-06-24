#include "../util/linked_list.h"
#include <stdio.h>

declareList(int, int);

int main(void){
    LinkedList(int)* list1 = NULL;
    llistPush(int, list1, 1);
    llistPush(int, list1, 2);

    printf("tail = %d\n", list1->tail->data);

    LinkedList(int)* list2 = NULL;
    llistPush(int, list2, 3);
    llistPush(int, list2, 4);

    printf("head = %d\n", list2->head->data);

    concate(list1, list2);
    listForEach(int, list1, node){
        printf("%d\n", node->data);
    }

    freeList(int, list2);
    printf("tail = %d\n",list1->tail->data);

    return 0;
}