#include <stdio.h>

#define MAX_SIZE 100  // Define a maximum size for the queue

typedef struct {
    int array[MAX_SIZE];
    int front;
    int rear;
    int count;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
    q->count = 0;
}

void enqueue(Queue *q, int element) {
    if (q->count == MAX_SIZE) {
        printf("Queue is full\n");
        return;
    }
    q->rear = (q->rear + 1) % MAX_SIZE;
    q->array[q->rear] = element;
    q->count++;
}

int dequeue(Queue *q) {
    if (q->count == 0) {
        printf("Queue is empty\n");
        return -1; // Return -1 to indicate error
    }
    int element = q->array[q->front];
    q->front = (q->front + 1) % MAX_SIZE;
    q->count--;
    return element;
}

int isEmpty(Queue *q) {
    return q->count == 0;
}

void printQueue(Queue *q) {
    if (isEmpty(q)) {
        printf("Queue is empty\n");
        return;
    }
    int i;
    int index = q->front;
    for (i = 0; i < q->count; i++) {
        printf("%d ", q->array[index]);
        index = (index + 1) % MAX_SIZE;
    }
    printf("\n");
}

int main() {
    Queue q;
    initQueue(&q);

    printf("Enter elements to enqueue (enter -1 to stop): \n");
    int element;
    while (1) {
        scanf("%d", &element);
        if (element == -1) break;
        enqueue(&q, element);
    }

    printQueue(&q);

    printf("Dequeued: %d\n", dequeue(&q));
    printQueue(&q);

    return 0;
}
