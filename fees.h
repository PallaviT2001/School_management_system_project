#ifndef FEES_H
#define FEES_H
#include "student.h"

extern struct Fees *feesHead;

struct Fees {
    int receiptNumber;
    float paidAmount;
    struct Student *studentDetails;
    struct Fees *next;
};

void insertFeestostudent(struct StudentList *students, int receiptNumber, float paidAmount, int studentId);
void displayFees();

#endif
