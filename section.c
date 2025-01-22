#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fileoperation.h"
#include "section.h"
#include "student.h"

struct Section *sectionHead = NULL;

struct Student *findStudentByIdfunctionforsection(struct StudentList *students, int studentId) {
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

void insertSectionToStudent(struct StudentList *students, int section_id, const char *section_name, int studentId) {
    struct Student *student =findStudentByIdfunctionforsection(students, studentId);
    if (student == NULL) {
        printf("Error: Student with ID %d not found!\n", studentId);
        return;
    }
    struct Section *newSection = (struct Section *)malloc(sizeof(struct Section));
    if (!newSection) {
        printf("Error: Memory allocation failed for Section node!\n");
        exit(EXIT_FAILURE);
    }
    newSection->section_id = section_id;
    strncpy(newSection->section_name, section_name, sizeof(newSection->section_name) - 1);
    newSection->section_name[sizeof(newSection->section_name) - 1] = '\0'; // Ensure null-terminated
    newSection->studentDetails = student;
    newSection->next = NULL;

    if (sectionHead == NULL) {
        sectionHead = newSection;
    } else {
        struct Section *temp = sectionHead;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSection;
    }

    printf("Section record added successfully for Student ID %d.\n", studentId);
    writeSectionToFile(&newSection);
}

void displaySections() {
    if (sectionHead == NULL) {
        printf("No section records available.\n");
        return;
    }

    printf("\n--- Section Details ---\n");
    struct Section *temp = sectionHead;

    while (temp != NULL) {
        printf("Section ID: %d\n", temp->section_id);
        printf("Section Name: %s\n", temp->section_name);

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
