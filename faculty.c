#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "faculty.h"
#include "fileoperation.h"

void insertFaculty(struct FacultyList *facultyList, int id, const char *name, const char *department, int age, const char *qualification)
{
    struct Faculty *newFaculty = (struct Faculty *)malloc(sizeof(struct Faculty));
    if (!newFaculty)
    {
        printf("Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }
    newFaculty->id = id;
    strncpy(newFaculty->name, name, sizeof(newFaculty->name) - 1);
    newFaculty->name[sizeof(newFaculty->name) - 1] = '\0';
    strncpy(newFaculty->department, department, sizeof(newFaculty->department) - 1);
    newFaculty->department[sizeof(newFaculty->department) - 1] = '\0';
    newFaculty->age = age;
    strncpy(newFaculty->qualification, qualification, sizeof(newFaculty->qualification) - 1);
    newFaculty->qualification[sizeof(newFaculty->qualification) - 1] = '\0';
    newFaculty->status = 'A';
    newFaculty->next = NULL;

    if (facultyList->head == NULL || strcmp(facultyList->head->name, newFaculty->name) > 0) {
        newFaculty->next = facultyList->head;
        facultyList->head = newFaculty;
    } else {
        struct Faculty *current = facultyList->head;
        while (current->next != NULL && strcmp(current->next->name, newFaculty->name) < 0) {
            current = current->next;
        }
        newFaculty->next = current->next;
        current->next = newFaculty;
    }

    addFacultyToFile(facultyList->head, *newFaculty);
}

void deleteFaculty(struct FacultyList *facultyList, int id) {
    if (facultyList->head == NULL) {
        printf("Faculty list is empty.\n");
        return;
    }

    struct Faculty *temp = facultyList->head, *prev = NULL;
    while (temp != NULL && temp->id != id) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Faculty with ID %d not found!\n", id);
        return;
    }
    if (prev == NULL) {
        facultyList->head = temp->next;
    } else {
        prev->next = temp->next;
    }
    deleteFacultyInFile(facultyList->head, id);
    free(temp);
    printf("Faculty deleted from the list and marked as deleted in the file.\n");
}

/*void updateFaculty(struct FacultyList *facultyList, int id)
{
    struct Faculty *temp = facultyList->head;
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
        printf("3. Department\n");
        printf("4. Qualification\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char newValue[50];
        switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->name, sizeof(temp->name), "%s", newValue);
            updateFacultyFieldInFile(facultyList->head, id, 1, newValue);
            break;
        case 2:
            printf("Enter new age: ");
            scanf("%d", &temp->age);
            snprintf(newValue, sizeof(newValue), "%d", temp->age);
            updateFacultyFieldInFile(facultyList->head, id, 2, newValue);
            break;
        case 3:
            printf("Enter new department: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->department, sizeof(temp->department), "%s", newValue);
            updateFacultyFieldInFile(facultyList->head, id, 3, newValue);
            break;
        case 4:
            printf("Enter new qualification: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->qualification, sizeof(temp->qualification), "%s", newValue);
            updateFacultyFieldInFile(facultyList->head, id, 4, newValue);
            break;
        default:
            printf("Invalid choice! Please select a valid option.\n");
            return;
        }
        printf("Faculty updated successfully!\n");
    } else {
        printf("Faculty with ID %d not found!\n", id);
    }
}*/

void displayFacultyDetails(struct FacultyList *facultyList) {
    if (facultyList->head == NULL) {
        printf("No faculty found!\n");
        return;
    }

    printf("------Faculty Details:------\n");
    struct Faculty *temp = facultyList->head;
    while (temp != NULL) {
        printf("ID: %d, Name: %s, Department: %s, Age: %d, Qualification: %s\n",
               temp->id, temp->name, temp->department, temp->age, temp->qualification);
        temp = temp->next;
    }
}

struct Faculty* mergeSortedFacultyLists(struct Faculty* left, struct Faculty* right) {
    if (!left) return right;
    if (!right) return left;

    struct Faculty* result = NULL;

    if (left->id <= right->id) {
        result = left;
        result->next = mergeSortedFacultyLists(left->next, right);
    } else {
        result = right;
        result->next = mergeSortedFacultyLists(left, right->next);
    }
    return result;
}

struct Faculty* getMiddleFaculty(struct Faculty* head) {
    if (!head) return head;

    struct Faculty* slow = head;
    struct Faculty* fast = head->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct Faculty* mergeSortFaculty(struct Faculty* head) {
    if (!head || !head->next) return head;

    struct Faculty* middle = getMiddleFaculty(head);
    struct Faculty* nextOfMiddle = middle->next;

    middle->next = NULL;

    struct Faculty* left = mergeSortFaculty(head);
    struct Faculty* right = mergeSortFaculty(nextOfMiddle);

    return mergeSortedFacultyLists(left, right);
}

void sortFacultiesByID(struct FacultyList *facultyList) {
    if (facultyList->head == NULL || facultyList->head->next == NULL) {
        printf("Not enough faculty to sort.\n");
        return;
    }
    facultyList->head = mergeSortFaculty(facultyList->head);
    printf("Faculty sorted by ID.\n");
    displayFacultyDetails(facultyList);
}

void sortFacultiesByName(struct FacultyList *facultyList) {
    if (facultyList->head == NULL || facultyList->head == NULL) {
        printf("Not enough faculty to sort.\n");
        return;
    }
    for (struct Faculty *i = facultyList->head; i != NULL; i = i->next) {
        for (struct Faculty *j = i->next; j != NULL; j = j->next) {
            if (strcmp(i->name, j->name) > 0) {
                struct Faculty temp = *i;
                *i = *j;
                *j = temp;
                temp.next = i->next;
                i->next = j->next;
                j->next = temp.next;
            }
        }
    }
    printf("Faculty sorted by Name.\n");
    displayFacultyDetails(facultyList);
}

void searchFacultyById(struct FacultyList *facultyList, int id) {
    struct Faculty *temp = facultyList->head;

    while (temp != NULL) {
        if (temp->id == id) {
            printf("Faculty found:\n");
            printf("ID: %d, Name: %s, Department: %s, Age: %d, Qualification: %s\n",
                   temp->id, temp->name, temp->department, temp->age, temp->qualification);
            return;
        }
        temp = temp->next;
    }
    printf("Faculty with ID %d not found!\n", id);
}

int getTotalFacultyCount(struct FacultyList *facultyList) {
    int count = 0;
    struct Faculty *temp = facultyList->head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

void updateFaculty(struct FacultyList *facultyList, int id) {
    struct Faculty *temp = facultyList->head;
    while (temp != NULL && temp->id != id) {
        temp = temp->next;
    }
    if (temp != NULL) {
        int choice;
        printf("Select the field to update:\n");
        printf("1. Name\n");
        printf("2. Department\n");
        printf("3. Age\n");
        printf("4. Qualification\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        char newValue[50];
        int newAge;
        switch (choice) {
        case 1:
            printf("Enter new name: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->name, sizeof(temp->name), "%s", newValue);
            updateFacultyFieldInFile(facultyList->head, id, 1, newValue);
            break;
        case 2:
            printf("Enter new department: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->department, sizeof(temp->department), "%s", newValue);
            updateFacultyFieldInFile(facultyList->head, id, 2, newValue);
            break;
        case 3:
            printf("Enter new age: ");
            scanf("%d", &newAge);
            temp->age = newAge;
            updateFacultyFieldInFile(facultyList->head, id, 3, &newAge);
            break;
        case 4:
            printf("Enter new qualification: ");
            scanf(" %[^\n]", newValue);
            snprintf(temp->qualification, sizeof(temp->qualification), "%s", newValue);
            updateFacultyFieldInFile(facultyList->head, id, 4, newValue);
            break;
        default:
            printf("Invalid choice! Please select a valid option.\n");
            return;
        }
        printf("Faculty updated successfully!\n");
    } else {
        printf("Faculty with ID %d not found!\n", id);
    }
}


