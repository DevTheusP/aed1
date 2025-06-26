/**
 * Definition for singly-linked list.
 * struct ListNode {
 * int val;
 * struct ListNode *next;
 * };
 */
struct ListNode* reverseList(struct ListNode* head) {
    // Ponteiro para o nó anterior. Começa como NULL, pois será o 'next' da nova cauda.
    struct ListNode* prev = NULL; 
    
    // Ponteiro para o nó atual que estamos visitando. Começa na cabeça da lista.
    struct ListNode* current = head; 
    
    // Ponteiro temporário para armazenar o próximo nó na lista original.
    struct ListNode* next_temp = NULL;

    // Percorre a lista até o fim.
    while (current != NULL) {
        // 1. Guarda a referência ao próximo nó antes de modificar o ponteiro 'next' do atual.
        // Se não fizermos isso, perderemos o resto da lista.
        next_temp = current->next; 
        
        // 2. Inverte o ponteiro: O 'next' do nó atual agora aponta para o nó anterior.
        current->next = prev;
        
        // 3. Move os ponteiros 'prev' e 'current' um passo à frente para a próxima iteração.
        prev = current;
        current = next_temp;
    }
    
    // Quando o loop termina, 'current' é NULL e 'prev' aponta para o último nó
    // que visitamos, que é a nova cabeça da lista invertida.
    return prev; 
}