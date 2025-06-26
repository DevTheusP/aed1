
typedef struct QueueNode {
    int data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    QueueNode* front;
    QueueNode* rear;
    int size;
} Queue;


Queue* createQueue() {
    Queue* q = (Queue*)malloc(sizeof(Queue));
    q->front = NULL;
    q->rear = NULL;
    q->size = 0;
    return q;
}

bool isQueueEmpty(Queue* q) {
    return q->front == NULL;
}

int queueSize(Queue* q) {
    return q->size;
}

void enqueue(Queue* q, int data) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = data;
    newNode->next = NULL;
    
    if (isQueueEmpty(q)) {
        q->front = q->rear = newNode;
    } else {
        q->rear->next = newNode;
        q->rear = newNode;
    }
    q->size++;
}

int dequeue(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    
    QueueNode* temp = q->front;
    int data = temp->data;
    q->front = q->front->next;
    
    if (q->front == NULL) {
        q->rear = NULL;
    }
    
    free(temp);
    q->size--;
    return data;
}

int queueFront(Queue* q) {
    if (isQueueEmpty(q)) {
        printf("Erro: Fila vazia!\n");
        return -1;
    }
    return q->front->data;
}

void destroyQueue(Queue* q) {
    while (!isQueueEmpty(q)) {
        dequeue(q);
    }
    free(q);
}


typedef struct {
    Queue* q1;  // Fila principal
    Queue* q2;  // Fila auxiliar
} MyStack;

/**
 * Cria uma nova pilha usando duas filas
 */
MyStack* myStackCreate() {
    MyStack* stack = (MyStack*)malloc(sizeof(MyStack));
    stack->q1 = createQueue();
    stack->q2 = createQueue();
    return stack;
}

/**
 * Adiciona um elemento no topo da pilha
 * Estratégia: Sempre inserir na q1, que mantém a ordem LIFO
 */
void myStackPush(MyStack* obj, int x) {
    // Adiciona o novo elemento na q1
    enqueue(obj->q1, x);
    
    printf("PUSH %d - Pilha agora tem %d elementos\n", x, queueSize(obj->q1));
}

/**
 * Remove e retorna o elemento do topo da pilha
 * Estratégia: Mover todos os elementos exceto o último de q1 para q2,
 * remover o último de q1, depois mover tudo de volta
 */
int myStackPop(MyStack* obj) {
    if (isQueueEmpty(obj->q1)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    
    // Se há apenas um elemento, removê-lo diretamente
    if (queueSize(obj->q1) == 1) {
        int result = dequeue(obj->q1);
        printf("POP %d - Pilha agora está vazia\n", result);
        return result;
    }
    
    // Mover todos os elementos exceto o último para q2
    while (queueSize(obj->q1) > 1) {
        int temp = dequeue(obj->q1);
        enqueue(obj->q2, temp);
    }
    
    // O último elemento em q1 é o topo da pilha
    int result = dequeue(obj->q1);
    
    // Mover todos os elementos de volta de q2 para q1
    while (!isQueueEmpty(obj->q2)) {
        int temp = dequeue(obj->q2);
        enqueue(obj->q1, temp);
    }
    
    printf("POP %d - Pilha agora tem %d elementos\n", result, queueSize(obj->q1));
    return result;
}

/**
 * Retorna o elemento do topo da pilha sem removê-lo
 * Estratégia: Similar ao pop, mas reinsere o elemento
 */
int myStackTop(MyStack* obj) {
    if (isQueueEmpty(obj->q1)) {
        printf("Erro: Pilha vazia!\n");
        return -1;
    }
    
    // Se há apenas um elemento, retorná-lo
    if (queueSize(obj->q1) == 1) {
        int result = queueFront(obj->q1);
        printf("TOP %d\n", result);
        return result;
    }
    
    // Mover todos os elementos exceto o último para q2
    while (queueSize(obj->q1) > 1) {
        int temp = dequeue(obj->q1);
        enqueue(obj->q2, temp);
    }
    
    // O último elemento em q1 é o topo da pilha
    int result = queueFront(obj->q1);
    
    // Mover o elemento do topo para q2 também
    int topElement = dequeue(obj->q1);
    enqueue(obj->q2, topElement);
    
    // Mover todos os elementos de volta de q2 para q1
    while (!isQueueEmpty(obj->q2)) {
        int temp = dequeue(obj->q2);
        enqueue(obj->q1, temp);
    }
    
    printf("TOP %d\n", result);
    return result;
}

/**
 * Verifica se a pilha está vazia
 */
bool myStackEmpty(MyStack* obj) {
    bool empty = isQueueEmpty(obj->q1);
    printf("EMPTY: %s\n", empty ? "true" : "false");
    return empty;
}

/**
 * Libera a memória da pilha
 */
void myStackFree(MyStack* obj) {
    destroyQueue(obj->q1);
    destroyQueue(obj->q2);
    free(obj);
}

/**
 * Função auxiliar para imprimir o estado atual da pilha
 */
void printStack(MyStack* obj) {
    if (isQueueEmpty(obj->q1)) {
        printf("Pilha: [vazia]\n");
        return;
    }
    
    printf("Pilha (topo -> base): [");
    
    // Criar uma fila temporária para não modificar a original
    Queue* temp = createQueue();
    
    // Mover elementos para temp e imprimir
    while (!isQueueEmpty(obj->q1)) {
        int val = dequeue(obj->q1);
        enqueue(temp, val);
    }
    
    // Criar array para inverter a ordem de impressão
    int* arr = (int*)malloc(temp->size * sizeof(int));
    int count = 0;
    
    // Mover de volta para q1 e preencher array
    while (!isQueueEmpty(temp)) {
        int val = dequeue(temp);
        arr[count++] = val;
        enqueue(obj->q1, val);
    }
    
    // Imprimir na ordem inversa (topo primeiro)
    for (int i = count - 1; i >= 0; i--) {
        printf("%d", arr[i]);
        if (i > 0) printf(", ");
    }
    
    printf("]\n");
    
    free(arr);
    destroyQueue(temp);
}