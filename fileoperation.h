#ifndef FILEOPERATION_H
#define FILEOPERATION_H
#include<stdio.h>

#define studentFile "students.txt"
#define facultyFile "faculty.txt"

void openStudentFileForReadingWriting();
void addStudentToFile(struct StudentList * students, struct Student *newStudent);
void deleteStudentInFile(struct StudentList * students, int id);
void updateStudentFieldInFile(struct StudentList * students, int id, int fieldToUpdate, const char *newValue);
void loadStudentRecords(struct StudentList *list);
void closeStudentFile();

void openFacultyFileForReadingWriting();
void addFacultyToFile(struct FacultyList *list, struct Faculty newFaculty);
void deleteFacultyInFile(struct FacultyList *list, int facultyID);
void updateFacultyFieldInFile(struct FacultyList *list, int facultyID, int field, void *newValue);
void loadFacultyRecords(struct FacultyList *list);
void closeFacultyFile();

void writeFeesToFile(struct Fees *newFees);
void loadFees(struct Fees **feesHead, struct StudentList *students);
void openFeesFileForReadingWriting();
void closeFeesFile();

void openSectionFileForReadingWriting();
void closeSectionFile();
void writeSectionToFile(struct Section *newSection);
void loadSections(struct Section **sectionHead, struct StudentList *students);

#endif

