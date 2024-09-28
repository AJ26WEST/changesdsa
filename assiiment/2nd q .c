#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the linked list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*) malloc(sizeof(Node));
    if (!newNode) {
        printf("Memory error\n");
        return NULL;
    }
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// Function to sort the linked list
Node* sortList(Node* head) {
    // Initialize three pointers for each type of node
    Node* zeroHead = createNode(0);
    Node* oneHead = createNode(0);
    Node* twoHead = createNode(0);
    Node* zeroTail = zeroHead;
    Node* oneTail = oneHead;
    Node* twoTail = twoHead;

    // Iterate through the list
    Node* current = head;
    while (current) {
        if (current->data == 0) {
            zeroTail->next = current;
            zeroTail = zeroTail->next;
        } else if (current->data == 1) {
            oneTail->next = current;
            oneTail = oneTail->next;
        } else {
            twoTail->next = current;
            twoTail = twoTail->next;
        }
        current = current->next;
    }

    // Concatenate the three lists
    oneTail->next = twoHead->next;
    zeroTail->next = oneHead->next;
    twoTail->next = NULL;

    // Return the sorted list
    Node* sortedHead = zeroHead->next;
    free(zeroHead);
    free(oneHead);
    free(twoHead);
    return sortedHead;
}

// Function to print the linked list
void printList(Node* head) {
    while (head) {
        printf("%d ", head->data);
        head = head->next;
    }
    printf("\n");
}

// Function to create a linked list from user input
Node* createListFromUserInput() {
    int n;
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    Node* head = NULL;
    Node* current = NULL;

    for (int i = 0; i < n; i++) {
        int data;
        printf("Enter node %d data : ", i + 1);
        scanf("%d", &data);

        Node* newNode = createNode(data);
        if (head == NULL) {
            head = newNode;
            current = newNode;
        } else {
            current->next = newNode;
            current = newNode;
        }
    }

    return head;
}

int main() {
    Node* head = createListFromUserInput();

    printf("Original List: ");
    printList(head);

    Node* sortedHead = sortList(head);

    printf("Sorted List: ");
    printList(sortedHead);

    return 0;
}
