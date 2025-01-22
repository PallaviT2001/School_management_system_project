#ifndef STUDENT_H
#define STUDENT_H

struct Student {
    int id;
    char name[50];
    int age;
    char contactNumber[20];
    char status;
    struct Student *next;
};
struct StudentList {
    struct Student *head;
    int studentCount;
};

void insertStudent(struct StudentList * students,int id, const char *name, int age, const char *contactNumber);
void deleteStudent(struct StudentList * students,int id);
void updateStudent(struct StudentList * students,int id);
void displayStudentDetails(struct StudentList * students);
void sortStudentsByID(struct StudentList * students);
void sortStudentsByName(struct StudentList * students);
void searchStudentById(struct StudentList * students,int id);
int getTotalStudentCount(struct StudentList * students);

#endif

