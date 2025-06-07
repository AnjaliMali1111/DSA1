#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a car
typedef struct Car {
    char model[50];
    char manufacturer[50];
    float price;
    float engine_capacity;
    struct Car *prev;
    struct Car *next;
} Car;

// Head of the doubly linked list
Car *head = NULL;

// Function to create a new node
Car *createCar(char *model, char *manufacturer, float price, float engine_capacity) {
    Car *newCar = (Car *)malloc(sizeof(Car));
    strcpy(newCar->model, model);
    strcpy(newCar->manufacturer, manufacturer);
    newCar->price = price;
    newCar->engine_capacity = engine_capacity;
    newCar->prev = newCar->next = NULL;
    return newCar; 
}

// Function to insert a new car
void insertCar() {
    char model[50], manufacturer[50];
    float price, engine_capacity;

    printf("Enter car model: ");
    scanf("%s", model);
    printf("Enter manufacturer: ");
    scanf("%s", manufacturer);
    printf("Enter price: ");
    scanf("%f", &price);
    printf("Enter engine capacity: ");
    scanf("%f", &engine_capacity);

    Car *newCar = createCar(model, manufacturer, price, engine_capacity);
    if (head == NULL) {
        head = newCar;
    } else {
        newCar->next = head;
        head->prev = newCar;
        head = newCar;
    }
    printf("Car added successfully!\n");
}

// Function to delete a car model
void deleteCar() {
    char model[50];
    printf("Enter the model to delete: ");
    scanf("%s", model);

    Car *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->model, model) == 0) {
            if (temp->prev) temp->prev->next = temp->next;
            if (temp->next) temp->next->prev = temp->prev;
            if (temp == head) head = temp->next;
            free(temp);
            printf("Car deleted successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Car model not found.\n");
}

// Function to update car price
void updateCarPrice() {
    char model[50];
    float newPrice;

    printf("Enter the car model to update price: ");
    scanf("%s", model);
    printf("Enter the new price: ");
    scanf("%f", &newPrice);

    Car *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->model, model) == 0) {
            temp->price = newPrice;
            printf("Price updated successfully!\n");
            return;
        }
        temp = temp->next;
    }
    printf("Car model not found.\n");
}

// Function to list cars within a price range
void listCarsByPrice() {
    float minPrice, maxPrice;
    printf("Enter minimum price: ");
    scanf("%f", &minPrice);
    printf("Enter maximum price: ");
    scanf("%f", &maxPrice);

    Car *temp = head;
    printf("Cars in the price range %.2f - %.2f:\n", minPrice, maxPrice);
    while (temp != NULL) {
        if (temp->price >= minPrice && temp->price <= maxPrice) {
            printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %.2f\n",
                   temp->model, temp->manufacturer, temp->price, temp->engine_capacity);
        }
        temp = temp->next;
    }
}

// Function to display details of a specific car model
void displayCarDetails() {
    char model[50];
    printf("Enter the car model: ");
    scanf("%s", model);

    Car *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->model, model) == 0) {
            printf("Model: %s, Manufacturer: %s, Price: %.2f, Engine Capacity: %.2f\n",
                   temp->model, temp->manufacturer, temp->price, temp->engine_capacity);
            return;
        }
        temp = temp->next;
    } 
    printf("Car model not found.\n");
}

// Menu-driven program
int main() {
    int choice;
    do {
        printf("\n--- Car Management System ---\n");
        printf("1. Insert new car\n");
        printf("2. Delete car\n");
        printf("3. Update car price\n");
        printf("4. List cars by price range\n");
        printf("5. Display car details\n"); 
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                insertCar();
                break;
            case 2:
                deleteCar();
                break;
            case 3:
                updateCarPrice();
                break;
            case 4:
                listCarsByPrice();
                break;
            case 5:
                displayCarDetails();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);

    return 0;
}