#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 5  // Maximum number of tickets in the queue

// Structure to represent a support ticket
struct Ticket {
    int id;
    char description[100];
};

// Circular Queue structure
struct CircularQueue {
    struct Ticket tickets[MAX_SIZE];
    int front, rear;
};

// Function to initialize the queue
void initQueue(struct CircularQueue* queue) {
    queue->front = -1;
    queue->rear = -1;
}

// Function to check if the queue is full
int isFull(struct CircularQueue* queue) {
    return (queue->rear + 1) % MAX_SIZE == queue->front;
}

// Function to check if the queue is empty
int isEmpty(struct CircularQueue* queue) {
    return queue->front == -1;
}

// Function to submit a new support ticket
void submitTicket(struct CircularQueue* queue, int id, const char* description) {
    if (isFull(queue)) {
        printf("Queue is full! Cannot submit new ticket.\n");
        return;
    }
    if (isEmpty(queue)) {
        queue->front = 0;
    }
    queue->rear = (queue->rear + 1) % MAX_SIZE;
    queue->tickets[queue->rear].id = id;
    strncpy(queue->tickets[queue->rear].description, description, sizeof(queue->tickets[queue->rear].description) - 1);
    queue->tickets[queue->rear].description[sizeof(queue->tickets[queue->rear].description) - 1] = '\0';  // Ensure null-termination
    printf("Ticket %d submitted successfully.\n", id);
}

// Function to process the next ticket in the queue
void processTicket(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("No tickets to process.\n");
        return;
    }
    printf("Processing ticket ID: %d\n", queue->tickets[queue->front].id);
    printf("Description: %s\n", queue->tickets[queue->front].description);
    if (queue->front == queue->rear) {
        // If there was only one ticket, reset the queue
        queue->front = queue->rear = -1;
    } else {
        queue->front = (queue->front + 1) % MAX_SIZE;
    }
}

// Function to display the current queue status
void displayQueue(struct CircularQueue* queue) {
    if (isEmpty(queue)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Current Tickets in Queue:\n");
    int i = queue->front;
    while (i != queue->rear) {
        printf("Ticket ID: %d, Description: %s\n", queue->tickets[i].id, queue->tickets[i].description);
        i = (i + 1) % MAX_SIZE;
    }
    printf("Ticket ID: %d, Description: %s\n", queue->tickets[queue->rear].id, queue->tickets[queue->rear].description);
}

// Main program
int main() {
    struct CircularQueue queue;
    initQueue(&queue);

    int choice, id;
    char description[100];

    while (1) {
        printf("\nCustomer Support Ticket System\n");
        printf("1. Submit Ticket\n");
        printf("2. Process Ticket\n");
        printf("3. Display Queue Status\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Submit Ticket
                printf("Enter Ticket ID: ");
                scanf("%d", &id);
                getchar();  // to consume the newline character left by scanf
                printf("Enter Ticket Description: ");
                fgets(description, sizeof(description), stdin);
                description[strcspn(description, "\n")] = '\0';  // Remove newline character
                submitTicket(&queue, id, description);
                break;

            case 2:
                // Process Ticket
                processTicket(&queue);
                break;

            case 3:
                // Display Queue Status
                displayQueue(&queue);
                break;

            case 4:
                // Exit
                printf("Exiting the program.\n");
                exit(0);

            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}
