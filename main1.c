#include "fileoperation.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "admin.h"
#include "student.h"
#include "faculty.h"
#include "fees.h"
#include "section.h"
#include "stdbool.h"

int studentIDCounter = 1;
int facultyIDCounter = 1;

enum MainMenuChoice {
    STUDENT_OPERATIONS = 1,
    FACULTY_OPERATIONS,
    FEES_OPERATIONS,
    SECTION_OPERATIONS,
    EXIT_PROGRAM
};

enum StudentMenuChoice {
    INSERT_STUDENT = 1,
    DELETE_STUDENT,
    UPDATE_STUDENT_DETAILS,
    DISPLAY_STUDENTS,
    SORT_STUDENTS_BY_ID,
    SORT_STUDENTS_BY_NAME,
    TOTAL_STUDENT_COUNT,
    SEARCH_STUDENT,
    EXIT_STUDENT
};

enum FacultyMenuChoice {
    INSERT_FACULTY = 1,
    DELETE_FACULTY,
    UPDATE_FACULTY_DETAILS,
    DISPLAY_FACULTIES,
    SORT_FACULTIES_BY_ID,
    SORT_FACULTIES_BY_NAME,
    TOTAL_FACULTY_COUNT,
    SEARCH_FACULTY,
    EXIT_FACULTY
};

enum FeesMenuChoice {
    INSERT_FEES_RECORD = 1,
    DISPLAY_FEES_RECORDS,
    EXIT_FEES
};

enum SectionMenuChoice {
    INSERT_SECTION = 1,
    DISPLAY_SECTIONS,
    EXIT_SECTION
};

void loadLastUsedIDs() {
    FILE *idFile = fopen("usedid's.txt", "r");
    if (idFile != NULL) {
        if (fscanf(idFile, "%d %d", &studentIDCounter, &facultyIDCounter) != 2) {
            printf("Error reading ID counters from file. Resetting to default values.\n");
            studentIDCounter = 1;
            facultyIDCounter = 1;
        }
        fclose(idFile);
    } else {
        printf("No, Existed ID's found\n");
        studentIDCounter = 1;
        facultyIDCounter = 1;
    }
}

void saveLastUsedIDs() {
    FILE *idFile = fopen("usedid's.txt", "w");
    if (idFile != NULL) {
        fprintf(idFile, "%d %d", studentIDCounter, facultyIDCounter);
        fclose(idFile);
    } else {
        printf("Error: Unable to save ID counters to file.\n");
    }
}

int generateStudentID() {
    return studentIDCounter++;
}

int generateFacultyID() {
    return facultyIDCounter++;
}

int mainprogram() {
    struct StudentList students = {0};
    struct FacultyList faculty = {0};

    loadLastUsedIDs();

    openStudentFileForReadingWriting();
    openFacultyFileForReadingWriting();
    openFeesFileForReadingWriting();
    openSectionFileForReadingWriting();

    loadStudentRecords(&students);
    loadFacultyRecords(&faculty);
    loadFees(&feesHead, &students);
    loadSections(&sectionHead, &students);

    if (!adminLogin()) {
        return 1;
    }

    int choice;
    while (true) {
        printf("--- Main Menu ---\n");
        printf("1. Student Operations\n");
        printf("2. Faculty Operations\n");
        printf("3. Fees Operations\n");
        printf("4. Section Operations\n");
        printf("5. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case STUDENT_OPERATIONS: {
            int studentChoice;
            while (true){
                printf("--- Student Operations ---\n");
                printf("1. Insert Student\n");
                printf("2. Delete Student\n");
                printf("3. Update Student Details\n");
                printf("4. Display Students\n");
                printf("5. Sort Students by ID\n");
                printf("6. Sort Students by Name\n");
                printf("7. Total Student Count\n");
                printf("8. Search Student by ID\n");
                printf("9. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &studentChoice);

                if (studentChoice == EXIT_STUDENT) break;

                switch (studentChoice) {
                case INSERT_STUDENT: {
                    int age;
                    char name[50], contactNumber[15];
                    int id = generateStudentID();
                    printf("Generated student ID: %d\n", id);

                    printf("Enter student name: ");
                    scanf(" %[^\n]", name);

                    printf("Enter student age: ");
                    scanf("%d", &age);

                    if (age <= 5 || age >= 30) {
                        printf("Invalid age. Student age must be between 5 and 30\n");
                        printf("Enter the valid age");
                        scanf("%d",&age);
                    }

                    printf("Enter student contact number: ");
                    scanf(" %[^\n]", contactNumber);
                    if (strlen(contactNumber) < 10 || strlen(contactNumber) > 12) {
                        printf("Invalid contact number. Must be between 10 and 12 digits.\n");
                        printf("Enter the valid contact number");
                        scanf(" %[^\n]", contactNumber);

                    }
                    insertStudent(&students, id, name, age, contactNumber);
                    saveLastUsedIDs();
                    break;
                }
                case DELETE_STUDENT: {
                    int id;
                    printf("Enter student ID to delete: ");
                    scanf("%d", &id);
                    deleteStudent(&students, id);
                    break;
                }
                case UPDATE_STUDENT_DETAILS: {
                    int id;
                    printf("Enter student ID to update: ");
                    scanf("%d", &id);
                    updateStudent(&students,id);
                    break;
                }
                case DISPLAY_STUDENTS:
                    displayStudentDetails(&students);
                    break;
                case SORT_STUDENTS_BY_ID:
                    sortStudentsByID(&students);
                    break;
                case SORT_STUDENTS_BY_NAME:
                    sortStudentsByName(&students);
                    break;
                case TOTAL_STUDENT_COUNT:
                    printf("Total student count: %d\n", getTotalStudentCount(&students));
                    break;
                case SEARCH_STUDENT:
                {
                    int id;
                    printf("Enter student ID to search: ");
                    scanf("%d", &id);
                    searchStudentById(&students,id);
                    break;
                }
                case EXIT_STUDENT:
                    printf("Exiting Student Operations.\n");
                    break;
                default:
                    printf("Invalid choice!\n");
                }
            }
            break;
        }
        case FACULTY_OPERATIONS: {
            int facultyChoice;
            while (true) {
                printf("--- Faculty Operations ---\n");
                printf("1. Insert Faculty\n");
                printf("2. Delete Faculty\n");
                printf("3. Update Faculty Details\n");
                printf("4. Display Faculties\n");
                printf("5. Sort Faculties by ID\n");
                printf("6. Sort Faculties by Name\n");
                printf("7. Total Faculty Count\n");
                printf("8. Search Faculty by ID\n");
                printf("9. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &facultyChoice);

                if (facultyChoice == EXIT_FACULTY) break;

                switch (facultyChoice) {
                case INSERT_FACULTY: {
                    int age;
                    char name[50], department[50], qualification[20];
                    int id = generateFacultyID();

                    printf("Generated faculty ID: %d\n", id);

                    printf("Enter faculty name: ");
                    scanf(" %[^\n]", name);

                    printf("Enter faculty age: ");
                    scanf("%d", &age);
                    if (age <= 25 || age >= 70) {
                        printf("Invalid age. Must be between 25 and 70\n");
                        printf("enter the valid faculty age");
                        scanf("%d", &age);
                    }

                    printf("Enter faculty department: ");
                    scanf(" %[^\n]", department);

                    printf("Enter faculty qualification: ");
                    scanf(" %[^\n]", qualification);

                    insertFaculty(&faculty, id, name, department, age, qualification);
                    saveLastUsedIDs();
                    break;
                }
                case DELETE_FACULTY: {
                    int id;
                    printf("Enter faculty ID to delete: ");
                    scanf("%d", &id);
                    deleteFaculty(&faculty,id);
                    break;
                }
                case UPDATE_FACULTY_DETAILS: {
                    int id;
                    printf("Enter faculty ID to update: ");
                    scanf("%d", &id);
                    updateFaculty(&faculty,id);
                    break;
                }
                case DISPLAY_FACULTIES:
                    displayFacultyDetails(&faculty);
                    break;
                case SORT_FACULTIES_BY_ID:
                    sortFacultiesByID(&faculty);
                    break;
                case SORT_FACULTIES_BY_NAME:
                    sortFacultiesByName(&faculty);
                    break;
                case TOTAL_FACULTY_COUNT:
                    printf("Total faculty count: %d\n", getTotalFacultyCount(&faculty));
                    break;
                case SEARCH_FACULTY:{
                    int id;
                    printf("Enter faculty ID to search: ");
                    scanf("%d", &id);
                    searchFacultyById(&faculty,id);
                    break;
                }
                case EXIT_STUDENT:
                    printf("Exiting Student Operations.\n");
                    break;
                default:
                    printf("Invalid choice!\n");
                }
            }
            break;
        }

        case FEES_OPERATIONS: {
            int feesChoice;
            while (true) {
                printf("--- Fees Operations ---\n");
                printf("1. Insert Fees Record\n");
                printf("2. Display Fees Records\n");
                printf("3. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &feesChoice);

                if (feesChoice == EXIT_FEES) break;

                switch (feesChoice) {
                case INSERT_FEES_RECORD: {
                    int studentID, receipt_number;
                    float paid_amount;
                    printf("Enter student ID: ");
                    scanf("%d", &studentID);
                    printf("Enter receipt number: ");
                    scanf("%d", &receipt_number);
                    printf("Enter paid amount: ");
                    scanf("%f", &paid_amount);
                    insertFeestostudent(&students, receipt_number, paid_amount, studentID);
                    break;
                }
                case DISPLAY_FEES_RECORDS:
                    displayFees();
                    break;
                default:
                    printf("Invalid choice!\n");
                }
            }
            break;
        }
        case SECTION_OPERATIONS: {
            int sectionChoice;
            while (true) {
                printf("--- Section Operations ---\n");
                printf("1. Insert Section Record\n");
                printf("2. Display Sections\n");
                printf("3. Exit\n");
                printf("Enter your choice: ");
                scanf("%d", &sectionChoice);

                if (sectionChoice == EXIT_SECTION) break;

                switch (sectionChoice) {
                case INSERT_SECTION: {
                    int studentID, section_id;
                    char section_name[20];
                    printf("Enter student ID: ");
                    scanf("%d", &studentID);
                    printf("Enter section ID: ");
                    scanf("%d", &section_id);
                    printf("Enter section name: ");
                    scanf(" %[^\n]", section_name);
                    insertSectionToStudent(&students, section_id, section_name, studentID);
                    break;
                }
                case DISPLAY_SECTIONS:
                    displaySections();
                    break;
                default:
                    printf("Invalid choice!\n");
                }
            }
            break;
        }
        case EXIT_PROGRAM:
            closeStudentFile();
            closeFacultyFile();
            closeFeesFile();
            closeSectionFile();
            printf("Exiting the program. Goodbye!\n");
            return 0;
        default:
            printf("Invalid choice!\n");
        }
    }
    return 1;

}
