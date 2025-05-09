#include <stdio.h>
#include <stdlib.h>


typedef struct ListNode {
    int val;
    struct ListNode* next;
} ListNode;

struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    int carry = 0;
    ListNode* newHead = (ListNode*)malloc(sizeof(ListNode));
    newHead->val = 0;
    newHead->next = NULL;
    ListNode* t = newHead;

    while (carry || l1 || l2) {
        carry += (l1 ? l1->val : 0) + (l2 ? l2->val : 0);
        t->next = (ListNode*)malloc(sizeof(ListNode));
        t->next->val = carry % 10;
        t->next->next = NULL;
        t = t->next;
        carry /= 10;
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    ListNode* result = newHead->next;
    free(newHead);
    return result;
}


ListNode* createNode(int val) {
    ListNode* node = (ListNode*)malloc(sizeof(ListNode));
    node->val = val;
    node->next = NULL;
    return node;
}


ListNode* createList(int arr[], int size) {
    if (size == 0) return NULL;
    ListNode* head = createNode(arr[0]);
    ListNode* current = head;
    for (int i = 1; i < size; i++) {
        current->next = createNode(arr[i]);
        current = current->next;
    }
    return head;
}


void printList(ListNode* head) {
    while (head) {
        printf("%d", head->val);
        if (head->next) printf(" -> ");
        head = head->next;
    }
    printf("\n");
}


void freeList(ListNode* head) {
    ListNode* temp;
    while (head) {
        temp = head;
        head = head->next;
        free(temp);
    }
}

// Função main para testar
int main() {
    
    int arr1[] = {2, 4, 3};
    int arr2[] = {5, 6, 4};
    ListNode* l1 = createList(arr1, 3);
    ListNode* l2 = createList(arr2, 3);

    
    printf("Lista 1: ");
    printList(l1);
    printf("Lista 2: ");
    printList(l2);

    
    ListNode* result = addTwoNumbers(l1, l2);

    
    printf("Resultado: ");
    printList(result);

    
    freeList(l1);
    freeList(l2);
    freeList(result);

    return 0;
}