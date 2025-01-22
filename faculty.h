#ifndef FACULTY_H
#define FACULTY_H

struct Faculty {
    int id;
    char name[50];
    char department[50];
    int age;
    char qualification[50];
    char status;
    struct Faculty *next;
};

struct FacultyList {
    struct Faculty *head;
    int facultyCount;
};

void insertFaculty(struct FacultyList *facultyList, int id, const char *name, const char *department, int age, const char *qualification);
void deleteFaculty(struct FacultyList *facultyList, int id);
void updateFaculty(struct FacultyList *facultyList, int id);
void displayFacultyDetails(struct FacultyList *facultyList);
void sortFacultiesByID(struct FacultyList *facultyList);
void sortFacultiesByName(struct FacultyList *facultyList);
int getTotalFacultyCount(struct FacultyList *facultyList);
void searchFacultyById(struct FacultyList *facultyList, int id);

#endif
