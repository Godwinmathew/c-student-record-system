#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct Student {
    int id;
    char name[50];
    int age;
    char course[50];
    float marks;
};

void addStudent() {

    struct Student s;
    FILE* fp;

    fp = fopen("students.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Name: ");
    scanf("%s", s.name);

    printf("Enter Age: ");
    scanf("%d", &s.age);

    printf("Enter Course: ");
    scanf("%s", s.course);

    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(s), 1, fp);

    fclose(fp);

    printf("\nStudent record added successfully!\n");
}

void viewStudents() {

    struct Student s;
    FILE* fp;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\n===== Student Records =====\n");

    while (fread(&s, sizeof(s), 1, fp)) {

        printf("\nID: %d", s.id);
        printf("\nName: %s", s.name);
        printf("\nAge: %d", s.age);
        printf("\nCourse: %s", s.course);
        printf("\nMarks: %.2f\n", s.marks);

        printf("---------------------------\n");
    }

    fclose(fp);
}

void searchStudent() {

    struct Student s;
    FILE* fp;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.id == id) {

            printf("\nStudent Found:\n");
            printf("ID: %d\n", s.id);
            printf("Name: %s\n", s.name);
            printf("Age: %d\n", s.age);
            printf("Course: %s\n", s.course);
            printf("Marks: %.2f\n", s.marks);

            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found.\n");

    fclose(fp);
}

void deleteStudent() {

    struct Student s;
    FILE* fp, * temp;
    int id, found = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(s), 1, fp)) {

        if (s.id == id) {
            found = 1;
        }
        else {
            fwrite(&s, sizeof(s), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nStudent record deleted successfully.\n");
    else
        printf("\nStudent not found.\n");
}

int main() {

    int choice;

    while (1) {

        printf("\n===== Student Record Management System =====\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

        case 1:
            addStudent();
            break;

        case 2:
            viewStudents();
            break;

        case 3:
            searchStudent();
            break;

        case 4:
            deleteStudent();
            break;

        case 5:
            printf("\nExiting program...\n");
            exit(0);

        default:
            printf("\nInvalid choice!\n");
        }
    }

    return 0;
}


