#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int rollNumber;
    float marks[5]; 
    float totalMarks;
    float average;
    char grade[3]; 
};


struct Student calculateGrade(struct Student student) {
    student.totalMarks = 0;
    for (int i = 0; i < 5; i++) {
        student.totalMarks += student.marks[i];
    }
    student.average = student.totalMarks / 5;

    
    if (student.average >= 90) {
        strcpy(student.grade, "A+");
    } else if (student.average >= 80) {
        strcpy(student.grade, "A");
    } else if (student.average >= 70) {
        strcpy(student.grade, "B+");
    } else if (student.average >= 60) {
        strcpy(student.grade, "B");
    } else {
        strcpy(student.grade, "F");
    }

    return student; 
}


void displayStudent(struct Student student) {
    printf("\nStudent Details:\n");
    printf("Name: %s\n", student.name);
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Total Marks: %.2f\n", student.totalMarks);
    printf("Grade: %s\n", student.grade);
}


void saveToFile(struct Student student) {
    FILE *file = fopen("students.txt", "a");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%s %d ", student.name, student.rollNumber);
    for (int i = 0; i < 5; i++) {
        fprintf(file, "%.2f ", student.marks[i]);
    }
    fprintf(file, "%.2f %.2f %s\n", student.totalMarks, student.average, student.grade);

    fclose(file);
    printf("Student data saved to file successfully!\n");
}


void displayAllStudents() {
    FILE *file = fopen("students.txt", "r"); 
    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    struct Student student;
    printf("\nAll Student Records:\n");
    while (fscanf(file, "%s %d", student.name, &student.rollNumber) != EOF) {
        for (int i = 0; i < 5; i++) {
            fscanf(file, "%f", &student.marks[i]);
        }
        fscanf(file,"%f %f %s", &student.totalMarks, &student.average, student.grade);

        displayStudent(student);
    }

    fclose(file);
}

main() {
    int choice;
    struct Student student;

    do {
        printf("\nStudent Grade Management System\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Input student details
                printf("Enter student name: ");
                getchar(); 
                fgets(student.name, 50, stdin);

                printf("Enter roll number: ");
                scanf("%d", &student.rollNumber);

                printf("Enter marks for 5 subjects:\n");
                for (int i = 0; i < 5; i++) {
                    printf("Subject %d: ", i + 1);
                    scanf("%f", &student.marks[i]);
                }

                
                student = calculateGrade(student); 

                
                saveToFile(student);
                break;

            case 2:
                displayAllStudents();
                break;

            case 3:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

