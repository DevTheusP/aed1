#include <stdio.h>
#include <stdlib.h>


//Matheus Persch


struct ListNode {
 int val;
 struct ListNode *next;
 };
 

struct ListNode* meio(struct ListNode* head){
    struct ListNode* slow = head;
    struct ListNode* fast = head->next;
    while(fast != NULL && fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}
struct ListNode* merge(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode head;
    struct ListNode* tail = &head;
    head.next = NULL;

    while (l1 != NULL && l2 != NULL) {
        if (l1->val < l2->val) {
            tail->next = l1;
            l1 = l1->next;
        } else {
            tail->next = l2;
            l2 = l2->next;
        }
        tail = tail->next;
    }

    
    if (l1 != NULL) {
        tail->next = l1;
    } else {
        tail->next = l2;
    }

    return head.next;
}

struct ListNode* sortList(struct ListNode* head) {
    if(head == NULL || head->next == NULL){
        return head;
    }

    struct ListNode* middle = meio(head);
    struct ListNode* aftermiddle = middle->next;
    middle->next = NULL; //acho o meio e divido a lista em 2

    struct ListNode* left = sortList(head); // parte esquerda vai ser dividida até o tamanho da parte ser 1 ou 0
    struct ListNode* right = sortList(aftermiddle); //mesma coisa
    struct ListNode* sorted = merge(left,right); //vou juntando e retornando cada partezinha menor, subindo na recursão
    return sorted;
}









struct ListNode* createNode(int value) {
    struct ListNode* newNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    if (!newNode) {
        perror("Falha na alocação de memória");
        exit(EXIT_FAILURE);
    }
    newNode->val = value;
    newNode->next = NULL;
    return newNode;
}


void printList(struct ListNode* head) {
    struct ListNode* current = head;
    while (current != NULL) {
        printf("%d -> ", current->val);
        current = current->next;
    }
    printf("NULL\n");
}

void freeList(struct ListNode* head) {
    struct ListNode* current = head;
    struct ListNode* nextNode;
    while (current != NULL) {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
}

//----------------------------------
// Função principal para execução
//----------------------------------
int main() {
    // Criando uma lista de exemplo: 4 -> 2 -> 1 -> 5 -> 3
    struct ListNode* head = createNode(4);
    head->next = createNode(2);
    head->next->next = createNode(1);
    head->next->next->next = createNode(5);
    head->next->next->next->next = createNode(3);

    printf("Lista original:\n");
    printList(head);

    // Chama a função de ordenação
    head = sortList(head);

    printf("\nLista ordenada:\n");
    printList(head);

    // Libera a memória alocada para a lista
    freeList(head);

    return 0;
}