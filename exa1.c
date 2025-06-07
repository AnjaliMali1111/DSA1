#include <stdio.h>
#include <string.h>
#define MAX 5 // Maximum size of the queue

// Structure to represent a ticket
typedef struct {
    int ticket_id;
    char src[20];
    char dest[20];
} Ticket;

// Declare the circular queue and its variables
Ticket tickets[MAX];
int front = -1;
int rear = -1;

// Check if the queue is full
int isFull() {
    return (rear + 1) % MAX == front;
}

// Check if the queue is empty
int isEmpty() {
    return front == -1;
}

// Add a ticket to the queue
void enqueue(int ticket_id, char *src, char *dest) {
    if (isFull()) {
        printf("Queue is full! Cannot add more tickets.\n");
        return;
    }
    if (isEmpty()) {
        front = 0;
    }
    rear = (rear + 1) % MAX;
    tickets[rear].ticket_id = ticket_id;
    strcpy(tickets[rear].src, src);
    strcpy(tickets[rear].dest, dest);
    printf("Ticket %d (From %s to %s) added to the queue.\n", ticket_id, src, dest);
}

// Remove a ticket from the queue
void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty! No tickets to process.\n");
        return;
    }
    printf("Processing ticket %d (From %s to %s).\n",
           tickets[front].ticket_id,
           tickets[front].src,
           tickets[front].dest);
    if (front == rear) {
        // Queue becomes empty
        front = rear = -1;
    } else {
        front = (front + 1) % MAX;
    }
}

// Display the tickets in the queue
void displayQueue() {
    if (isEmpty()) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Current tickets in queue:\n");
    int i = front;
    while (1) {
        printf("Ticket ID: %d, From: %s, To: %s\n",
               tickets[i].ticket_id,
               tickets[i].src,
               tickets[i].dest);
        if (i == rear) {
            break;
        }
        i = (i + 1) % MAX;
    }
}

int main() {
    int choice, ticket_id;
    char src[20], dest[20];

    do {
        printf("\n1. Add Ticket\n2. Process Ticket\n3. Display Queue\n4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            printf("Enter ticket ID: ");
            scanf("%d", &ticket_id);
            printf("Enter source: ");
            scanf("%s", src);
            printf("Enter destination: ");
            scanf("%s", dest);
            enqueue(ticket_id, src, dest);
            break;
        case 2:
            dequeue();
            break;
        case 3:
            displayQueue();
            break;
        case 4:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice! Try again.\n");
        }
    } while (choice != 4);

    return 0;
}