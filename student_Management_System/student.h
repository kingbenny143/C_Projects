#ifndef STUDENT_H
#define STUDENT_H

struct student {
    int id;
    char name[30];
    float marks;
};

void addStudent();
void viewStudent();
void searchStudent();
void updateStudent();
void removeStudent();

#endif