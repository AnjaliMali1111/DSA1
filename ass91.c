#include <stdio.h>

// Structure to store student data
typedef struct {
    int rollNo;
    char name[50];
    float percentage;
} Student;

// Function to input student data
void inputStudents(Student students[], int n) {
    for (int i = 0; i < n; i++) {
        printf("\nEnter details for student %d:\n", i + 1);
        printf("Roll No: ");
        scanf("%d", &students[i].rollNo);
        printf("Name: ");
        scanf(" %s", students[i].name);
        printf("Percentage: ");
        scanf("%f", &students[i].percentage);
    }
}

// Function to display a student's details
void displayStudent(Student student) {
    printf("\nRoll No: %d\n", student.rollNo);
    printf("Name: %s\n", student.name);
    printf("Percentage: %.2f\n", student.percentage);
}

// Function to sort students by roll number
void sortStudents(Student students[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (students[j].rollNo > students[j + 1].rollNo) {
                Student temp = students[j];
                students[j] = students[j + 1];
                students[j + 1] = temp;
            }
        }
    }
}

// Function to search for a student using binary search
int binarySearch(Student students[], int n, int rollNo) {
    int left = 0, right = n - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (students[mid].rollNo == rollNo) {
            return mid; // Found
        } else if (students[mid].rollNo < rollNo) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1; // Not found
}

int main() {
    int n, rollNo, index;

    // Input the number of students
    printf("Enter the number of students: ");
    scanf("%d", &n);

    // Create an array to store students
    Student students[n];

    // Input student details
    inputStudents(students, n);

    // Sort students by roll number
    sortStudents(students, n);


    // Search for a student
    printf("\nEnter the roll number to search: ");
    scanf("%d", &rollNo);

    index = binarySearch(students, n, rollNo);

    if (index != -1) {
        printf("\nStudent found:\n");
        displayStudent(students[index]);
    } else {
        printf("\nStudent with roll number %d not found.\n", rollNo);
    }

    return 0;
}