#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"
#include "fileoperation.h"

void insertStudent(struct StudentList * students,int id, const char *name, int age, const char *contactNumber)
{
    struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
    if (!newStudent)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newStudent->id = id;
    strncpy(newStudent->name, name, sizeof(newStudent->name) - 1);
    newStudent->name[sizeof(newStudent->name) - 1] = '\0';
    newStudent->age = age;
    strncpy(newStudent->contactNumber, contactNumber, sizeof(newStudent->contactNumber) - 1);
    newStudent->contactNumber[sizeof(newStudent->contactNumber) - 1] = '\0';
    newStudent->status = 'A';
    newStudent->next = NULL;

    if (students->head == NULL || strcmp(students->head->name, newStudent->name) > 0) {
        newStudent->next = students->head;
        students->head= newStudent;
    } else {
        struct Student *current = students->head;
        while (current->next != NULL && strcmp(current->next->name, newStudent->name) < 0) {
            current = current->next;
        }
        newStudent->next = current->next;
        current->next = newStudent;
    }
    addStudentToFile(students->head, newStudent);
}

void deleteStudent(struct StudentList * students,int id) {
    if (students->head == NULL) {
        printf("Student list is empty.\n");
        return;
    }

    struct Student *temp = students->head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Student with ID %d not found!\n", id);
        return;
    }
    if (prev == NULL) {
        students->head = temp->next;
    } else {
        prev->next = temp->next;
    }
    deleteStudentInFile(students->head, id);
    free(temp);
    printf("Student deleted from the list and marked as deleted in the file.\n");
}

/*void updateStudent(struct StudentList * students, int id)
{
    struct Student *temp = students->head;
    while (temp != NULL && temp->id != id)
    {
        temp = temp->next;
    }
    if (temp != NULL)
    {
        int choice;
        printf("Select the field to update:\n");
        printf("1. Name\n");
        printf("2. Age\n");
        printf("3. Contact Number\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char newValue[50];
        switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->name, sizeof(temp->name), "%s", newValue);
            updateStudentFieldInFile(students->head, id, 1, newValue);
            break;
        case 2:
            printf("Enter new age: ");
            scanf("%d", &temp->age);
            snprintf(newValue, sizeof(newValue), "%d", temp->age);
            updateStudentFieldInFile(students->head, id, 2, newValue);
            break;
        case 3:
            printf("Enter new contact number: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->contactNumber, sizeof(temp->contactNumber), "%s", newValue);
            updateStudentFieldInFile(students->head, id, 3, newValue);
            break;
        default:
            printf("Invalid choice! Please select a valid option.\n");
            return;
        }
        printf("Student updated successfully!\n");
    }
    else {
        printf("Student with ID %d not found!\n", id);
    }
}*/

void displayStudentDetails(struct StudentList * students) {
    if (students->head == NULL) {
        printf("No students found!\n");
        return;
    }

    printf("------Student Details:------\n");
    struct Student *temp = students->head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Age: %d, Contact Number: %s\n",
               temp->id, temp->name, temp->age, temp->contactNumber);
        temp = temp->next;
    }
}

struct Student* mergeSortedLists(struct Student* left, struct Student* right) {
    if (!left) return right;
    if (!right) return left;

    struct Student* result = NULL;

    if (left->id <= right->id) {
        result = left;
        result->next = mergeSortedLists(left->next, right);
    } else {
        result = right;
        result->next = mergeSortedLists(left, right->next);
    }
    return result;
}

struct Student* getMiddle(struct Student* head) {
    if (!head) return head;

    struct Student* slow = head;
    struct Student* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct Student* mergeSort(struct Student* head) {
    if (!head || !head->next) return head;

    struct Student* middle = getMiddle(head);
    struct Student* nextOfMiddle = middle->next;

    middle->next = NULL;

    struct Student* left = mergeSort(head);
    struct Student* right = mergeSort(nextOfMiddle);

    return mergeSortedLists(left, right);
}

void sortStudentsByID(struct StudentList * students) {
    if (students->head== NULL || students->head->next == NULL) {
        printf("Not enough students to sort.\n");
        return;
    }
    students->head = mergeSort(students->head);
    printf("Students sorted by ID.\n");
    displayStudentDetails(students);
}

void sortStudentsByName(struct StudentList * students) {
    if (students->head == NULL || students->head == NULL) {
        printf("Not enough students to sort.\n");
        return;
    }
    for (struct Student *i = students->head; i != NULL; i = i->next) {
        for (struct Student *j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
                struct Student temp = *i;
                *i = *j;
                *j = temp;
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
    printf("Students sorted by Name.\n");
    displayStudentDetails(students);
}

void searchStudentById(struct StudentList * students,int id) {
    struct Student *temp = students->head;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("Student found:\n");
            printf("ID: %d, Name: %s, Age: %d, Contact Number: %s\n",
                   temp->id, temp->name, temp->age, temp->contactNumber);
            return;
        }
        temp = temp->next;
    }
    printf("Student with ID %d not found!\n", id);
}

int getTotalStudentCount(struct StudentList * students) {
    int count = 0;
    struct Student *temp = students->head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void updateStudent(struct StudentList *students, int id) {
    struct Student *temp = students->head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp != NULL) {
        int choice;
        printf("Select the field to update:\n");
        printf("1. Name\n");
        printf("2. Age\n");
        printf("3. Contact Number\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char newValue[50];
        int newAge;
        switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->name, sizeof(temp->name), "%s", newValue);
            updateStudentFieldInFile(students->head, id, 1, newValue);
            break;
        case 2:
            printf("Enter new age: ");
            scanf("%d", &newAge);
            temp->age = newAge;
            updateStudentFieldInFile(students->head, id, 2, &newAge);
            break;
        case 3:
            printf("Enter new contact number: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->contactNumber, sizeof(temp->contactNumber), "%s", newValue);
            updateStudentFieldInFile(students->head, id, 3, newValue);
            break;
        default:
            printf("Invalid choice! Please select a valid option.\n");
            return;
        }
        printf("Student updated successfully!\n");
    } else {
        printf("Student with ID %d not found!\n", id);
    }
}



