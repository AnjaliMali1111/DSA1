#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Define a structure to store student information
typedef struct {
    int rollNo;
    char name[50];
    float percentage;
} Student;

// Function to swap two students
void swap(Student *a, Student *b) {
    Student temp = *a;
    *a = *b;
    *b = temp;
}

// Bubble sort function to sort students based on percentage in descending order
void bubbleSort(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            if (students[j].percentage < students[j + 1].percentage) {
                swap(&students[j], &students[j + 1]);
            }
        }
    }
}

int main() {
    int n;

    // Input the number of students
    printf("Enter number of students: ");
    scanf("%d", &n);

    // Ensure there are enough students to find the top 10
    if (n < 10) {
        printf("There are fewer than 10 students. Please input at least 10 students.\n");
        return 1;
    }

    Student students[MAX_STUDENTS];

    // Input student data
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].rollNo);
        getchar();  // Consume the newline character left by scanf
        printf("Name: ");
        fgets(students[i].name, 50, stdin);
        students[i].name[strcspn(students[i].name, "\n")] = '\0';  // Remove the trailing newl12ine
        printf("Percentage: ");
        scanf("%f", &students[i].percentage);
    }

    // Sort the students by percentage using Bubble Sort
    bubbleSort(students, n);

    // Display the top 10 students
    printf("\nTop 10 Toppers:\n");
    for (int i = 0; i < 10 && i < n; i++) {
        printf("\nRank %d:\n", i + 1);
        printf("Roll No: %d\n", students[i].rollNo);
        printf("Name: %s\n", students[i].name);
        printf("Percentage: %.2f\n", students[i].percentage);
    }

    return 0;
}
