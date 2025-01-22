#ifndef SECTION_H
#define SECTION_H
#include "student.h"

extern struct Section *sectionHead;

struct Section {
    int section_id;
    char section_name[50];
    struct Student *studentDetails;
    struct Section *next;
};

void insertSectionToStudent(struct StudentList *students, int section_id, const char *section_name, int studentId);
void displaySections();

#endif
