#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for the node of the BST 
typedef struct Node {
    char name[100];
    char phone[20];
    struct Node* left;
    struct Node* right;
} Node;

// Function to create a new node
Node* createNode(char name[], char phone[]) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

// Function to insert a new node into the BST
Node* insertNode(Node* root, char name[], char phone[]) {
    if (root == NULL) {
        return createNode(name, phone);
    }

    if (strcmp(name, root->name) < 0) {
        root->left = insertNode(root->left, name, phone);
    } else if (strcmp(name, root->name) > 0) {
        root->right = insertNode(root->right, name, phone);
    } else {
        printf("Duplicate entry found. The name already exists.\n");
    }
    return root;
}

// Function to search for a name in the BST
Node* searchNode(Node* root, char name[]) {
    if (root == NULL || strcmp(root->name, name) == 0) {
        return root;
    }

    if (strcmp(name, root->name) < 0) {
        return searchNode(root->left, name);
    } else {
        return searchNode(root->right, name);
    }
}

// Function to find the minimum node in a BST
Node* findMin(Node* root) {
    while (root && root->left != NULL) {
        root = root->left;
    }
    return root;
}

// Function to delete a node from the BST
Node* deleteNode(Node* root, char name[]) {
    if (root == NULL) {
        return root;
    }

    // Find the node to delete
    if (strcmp(name, root->name) < 0) {
        root->left = deleteNode(root->left, name);
    } else if (strcmp(name, root->name) > 0) {
        root->right = deleteNode(root->right, name);
    } else {
        // Node found, perform deletion
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }

        // Node with two children, get the inorder successor
        Node* temp = findMin(root->right);

        // Copy the inorder successor's content to this node
        strcpy(root->name, temp->name);
        strcpy(root->phone, temp->phone);

        // Delete the inorder successor
        root->right = deleteNode(root->right, temp->name);
    }
    return root;
}

// Function to print the entire phone list (in-order traversal)
void printInOrder(Node* root) {
    if (root == NULL) {
        return;
    }
    printInOrder(root->left);
    printf("Name: %s, Phone: %s\n", root->name, root->phone);
    printInOrder(root->right);
}

// Main function to interact with the user
int main() {
    Node* root = NULL;
    int choice;
    char name[100], phone[20];

    while (1) {
        printf("\nPhone Directory Menu:\n");
        printf("1. Insert new name\n");
        printf("2. Search for a name\n");
        printf("3. Delete a name\n");
        printf("4. Print entire phone list\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // To consume the newline character

        switch (choice) {
            case 1:
                // Insert a new name and phone number
                printf("Enter name: ");
                scanf("%s",name);
                  // Remove newline character

                printf("Enter phone number: ");
                scanf("%s",phone);
                  // Remove newline character

                root = insertNode(root, name, phone);
                break;

            case 2:
                // Search for a name
                printf("Enter name to search: ");
                  scanf("%s",name); 

                Node* result = searchNode(root, name);
                if (result) {
                    printf("Found: Name: %s, Phone: %s\n", result->name, result->phone);
                } else {
                    printf("Name not found.\n");
                }
                break;

            case 3:
                // Delete a name
                printf("Enter name to delete: ");
                 scanf("%s",name); 
                  // Remove newline character

                root = deleteNode(root, name);
                printf("Name %s deleted successfully.\n", name);
                break;

            case 4:
                // Print the entire phone list
                printf("Phone Directory:\n");
                printInOrder(root);
                break;

            case 5:
                // Exit the program
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    }     

    return 0;
}
