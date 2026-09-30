#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    int id;
    char name[50];
    float marks;
};

/* Function declarations */
void addStudent();
void deleteStudent();
void updateStudent();
void searchStudent();
void displayStudents();

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================\n");
        printf("     STUDENT MANAGEMENT SYSTEM\n");
        printf("====================================\n");
        printf("1. Add Student\n");
        printf("2. Delete Student\n");
        printf("3. Update Student\n");
        printf("4. Search Student\n");
        printf("5. Display Students\n");
        printf("6. Exit\n");
        printf("====================================\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudent();
                break;

            case 2:
                deleteStudent();
                break;

            case 3:
                updateStudent();
                break;

            case 4:
                searchStudent();
                break;

            case 5:
                displayStudents();
                break;

            case 6:
                printf("\nThank you for using Student Management System.\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}

/* Add Student */
void addStudent()
{
    struct Student s;
    FILE *fp;

    fp = fopen("students.dat", "ab");

    if (fp == NULL)
    {
        printf("\nError opening file!\n");
        return;
    }

    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);

    printf("Enter Student Name: ");
    scanf(" %[^\n]", s.name);

    printf("Enter Student Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);

    fclose(fp);

    printf("\nStudent added successfully!\n");
}

/* Delete Student */
void deleteStudent()
{
    struct Student s;
    FILE *fp, *temp;
    int id;
    int found = 0;

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    if (temp == NULL)
    {
        printf("\nError creating temporary file!\n");
        fclose(fp);
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.id == id)
        {
            found = 1;
        }
        else
        {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        printf("\nStudent deleted successfully!\n");
    else
        printf("\nStudent ID not found!\n");
}

/* Update Student */
void updateStudent()
{
    struct Student s;
    FILE *fp;
    int id;
    int found = 0;

    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);

    fp = fopen("students.dat", "rb+");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.id == id)
        {
            printf("\nEnter new name: ");
            scanf(" %[^\n]", s.name);

            printf("Enter new marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -sizeof(struct Student), SEEK_CUR);

            fwrite(&s, sizeof(struct Student), 1, fp);

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (found)
        printf("\nStudent updated successfully!\n");
    else
        printf("\nStudent ID not found!\n");
}

/* Search Student */
void searchStudent()
{
    struct Student s;
    FILE *fp;
    int id;
    int found = 0;

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        if (s.id == id)
        {
            printf("\nStudent Found!\n");
            printf("--------------------------\n");
            printf("Student ID   : %d\n", s.id);
            printf("Student Name : %s\n", s.name);
            printf("Marks        : %.2f\n", s.marks);
            printf("--------------------------\n");

            found = 1;
            break;
        }
    }

    fclose(fp);

    if (!found)
        printf("\nStudent ID not found!\n");
}

/* Display Students */
void displayStudents()
{
    struct Student s;
    FILE *fp;
    int count = 0;

    fp = fopen("students.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo student records found!\n");
        return;
    }

    printf("\n====================================\n");
    printf("         STUDENT RECORDS\n");
    printf("====================================\n");

    while (fread(&s, sizeof(struct Student), 1, fp))
    {
        printf("\nStudent ID   : %d\n", s.id);
        printf("Student Name : %s\n", s.name);
        printf("Marks        : %.2f\n", s.marks);
        printf("------------------------------------\n");

        count++;
    }

    fclose(fp);

    if (count == 0)
        printf("No student records available.\n");
}
