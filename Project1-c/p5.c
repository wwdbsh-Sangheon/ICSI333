#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct student_struct
{
    char name[16];
    int age;
    float gpa;
    struct student_struct *next;
} Student;

Student head; //The head of the linked list

Student *makeStudent(char name[16], int age, double gpa); // Prototypes
Student *findTopStudent();
void push(Student *student);
float getAverageGPA();
void freeMemory(); // I added one more function for deallocating memory.

int main(int argc, char **argv)
{
    if(argc != 2){
        perror("ERROR: Wrong number of command line args!\n");
        return -1;
    }

    head.next = NULL; //initialize that the linked list is empty.
    FILE * file;
    file = fopen(argv[1] , "r");
    if (!file)
    {
        perror("ERROR opening file!\n");
        return -1;
    }

    char s1[16];
    char s2[16];
    char s3[16];

    while (fscanf(file, "%s %s %s", s1,s2,s3)!=EOF)
        push(makeStudent(s1, atoi(s2), atof(s3))); // Creating nodes by calling push function.
    
    fclose(file);

    Student *topStudent = findTopStudent(); // Storing top student node into topStudent pointer variable from findTopStudent function.
    printf("The Student with the best GPA is: %s\n", topStudent->name);
    printf("The average GPA is: %.2f\n", getAverageGPA());
    freeMemory(); // Deallocating memory.

    return 0;
}

Student *makeStudent(char name[16], int age, double gpa)
{
    Student* student = (Student*)malloc(sizeof(Student)); // Allocating memory.
    
    strcpy(student->name, name); // Storing name into node.
    student->age = age; // Storing age into node.
    student->gpa = gpa; // Storing gpa into node.

    return student; // Return Student pointer type variable.
}

void push(Student *student)
{
    if(head.next == NULL) // Condition: next node of head is NULL.
    {
        head.next = student; // Storing student's reference into next node of head.
        student->next = NULL; // Storing NULL into next node of student.
    }
    else
    {
        student->next = head.next; // Stroing reference of head's next node into student's next node.
        head.next = student; // Storing student's reference into head's next node.
    }
}

Student *findTopStudent()
{
    float max = 0.0;

    Student *cur, *top;

    for(cur = head.next; cur != NULL; cur = cur->next)
    {
        if(max < cur->gpa) // Condition: max is less than current node's gpa.
        {
            max = cur->gpa;
            top = cur; // Storing current node's reference into top.
        }
    }

    return top;
}

float getAverageGPA()
{
    float avg = 0.0;
    int num = 0;
      
    Student* cur;

    for(cur = head.next; cur != NULL; cur = cur->next)
    {
        avg += cur->gpa; // Increasing avg by adding current node's gpa.
        num++;
    }

    avg /= num;

    return avg;
}

void freeMemory()
{
    Student* cur;
    Student* del = head.next; // Student pointer variable for deleting nodes.

    for(cur = head.next; cur != NULL; cur = cur->next)
    {
        free(del); // Deallocating current node's memory.
        del = NULL;
        del = cur->next; // Storing reference of current node's next node into del.
    }

    free(del);
    del = NULL;
}