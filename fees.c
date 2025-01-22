#include <stdio.h>
#include <stdlib.h>
#include "fileoperation.h"
#include "student.h"
#include "fees.h"

struct Fees *feesHead = NULL;

struct Student *findStudentById(struct StudentList *students, int studentId) {
    if (students == NULL || students->head == NULL) {
        return NULL;
    }

    struct Student *temp = students->head;
    while (temp != NULL) {
        if (temp->id == studentId) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void insertFeestostudent(struct StudentList *students, int receiptNumber, float paidAmount, int studentId) {
    struct Student *student = findStudentById(students, studentId);
    if (student == NULL) {
        printf("Error: Student with ID %d not found!\n", studentId);
        return;
    }
    struct Fees *newFees = (struct Fees *)malloc(sizeof(struct Fees));
    if (!newFees) {
        printf("Error: Memory allocation failed for Fees node!\n");
        exit(EXIT_FAILURE);
    }
    newFees->receiptNumber = receiptNumber;
    newFees->paidAmount = paidAmount;
    newFees->studentDetails = student;
    newFees->next = NULL;

    if (feesHead == NULL) {
        feesHead = newFees;
    } else {
        struct Fees *temp = feesHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newFees;
    }

    printf("Fees record added successfully for Student ID %d.\n", studentId);
    writeFeesToFile(newFees);
}

void displayFees(){
    if (feesHead == NULL) {
        printf("No fees records available.\n");
        return;
    }

    printf("--- Fees Details ---\n");
    struct Fees *temp = feesHead;

    while (temp != NULL) {
        printf("Receipt Number: %d\n", temp->receiptNumber);
        printf("Paid Amount: %.2f\n", temp->paidAmount);

        if (temp->studentDetails != NULL) {
            struct Student *student = temp->studentDetails;
            printf("Student Details:\n");
            printf("  ID: %d\n", student->id);
            printf("  Name: %s\n", student->name);
            printf("  Age: %d\n", student->age);
            printf("  Contact Number: %s\n", student->contactNumber);
        } else {
            printf("Error: Associated student details not found.\n");
        }

        printf("\n");
        temp = temp->next;
    }
}




















