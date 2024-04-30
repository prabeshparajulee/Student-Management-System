#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addstudent();
void studentrecord();
void searchstudent();
void delete ();

struct student {
  char firstname[20];
  char lastname[20];
  int rollno;
  char class[10];
  char address[20];
  float gpa;
};
int main() {
  int choice;
  while (choice != 5) {
    printf("\t\t\t=====STUDENT MANAGEMENT SYSTEM======");
    printf("\n\n\n\t\t\t\t 1. Add Student record\n");
    printf("\t\t\t\t 2. Student records\n");
    printf("\t\t\t\t 3. Search Student\n");
    printf("\t\t\t\t 4. Delete Student record\n");
    printf("\t\t\t\t 5. Exit\n");
    printf("\t\t\t\t _________________________________\n");
    printf("\t\t\t\t ");
    scanf("%d", &choice);

    switch (choice) {

    case 1:
      addstudent();
      break;

    case 2:
      studentrecord();
      break;

    case 3:
      searchstudent();
      break;

    case 4:
      delete ();
      break;

    case 5:
      printf("\n\t\t\t\tThank you for using our system:)\n\n");
      exit(0);
      break;
    }
  }
}
void addstudent() {
  char another_record;
  FILE *fp;
  struct student info;

  do {
    printf("\t\t\t\t======Add Student info======\n\n\n");
    fp = fopen("student_info.txt", "a");
    printf("\n\t\t\tEnter first name: ");
    scanf("%s", info.firstname);
    printf("\n\t\t\tEnter last name: ");
    scanf("%s", info.lastname);
    printf("\n\t\t\tEnter roll no: ");
    scanf("%d", &info.rollno);
    printf("\n\t\t\tEnter class: ");
    scanf("%s", info.class);
    printf("\n\t\t\tEnter address: ");
    scanf("%s", info.address);
    printf("\n\t\t\tEnter GPA: ");
    scanf("%f", &info.gpa);
    printf("\n\t\t\t_______________________________]");
    if (fp == NULL) {
      printf("Error opening the file");
    } else {
      printf("\n\t\t\t Record stored successfully");
    }
    fwrite(&info, sizeof(struct student), 1, fp);
    fclose(fp);

    printf("\n\t\t\tDo you want to add another record(y/n): ");
    scanf("%s", &another_record);

  } while (another_record == 'y' || another_record == 'Y');
}
void studentrecord() {
  FILE *fp;
  struct student info;
  fp = fopen("student_info.txt", "r");
  printf("\t\t\t\t======Student Records======\n\n\n");
  if (fp == NULL) {
    printf("\n\t\t\tError opening the file");
  } else {
    printf("\t\t\t\tRecords\n");
    printf("\t\t\t\t_______________\n\n");
  }
  while (fread(&info, sizeof(struct student), 1, fp)) {
    printf("\n\t\t\t\tStudent name : %s %s", info.firstname, info.lastname);
    printf("\n\t\t\t\tRoll no      : %d", info.rollno);
    printf("\n\t\t\t\tClass        : %s", info.class);
    printf("\n\t\t\t\tAddress      : %s", info.address);
    printf("\n\t\t\t\tGPA          : %f", info.gpa);
    printf("\n\t\t\t\t_______________________________\n\n");
  }
  fclose(fp);
}
void searchstudent() {
  FILE *fp;
  struct student info;
  int rollno, found = 0;
  char firstname[20];
  fp = fopen("student_info.txt", "r");
  printf("\t\t\t\t======Search Student======\n\n\n");
  printf("\t\t\tEnter roll no: ");
  scanf("%d", &rollno);

  while (fread(&info, sizeof(struct student), 1, fp)) {
    if (info.rollno == rollno) {
      found = 1;
      printf("\n\t\t\t\tStudent name : %s %s", info.firstname, info.lastname);
      printf("\n\t\t\t\tRoll no      : %d", info.rollno);
      printf("\n\t\t\t\tClass        : %s", info.class);
      printf("\n\t\t\t\tAddress      : %s", info.address);
      printf("\n\t\t\t\tPercentage   : %f", info.gpa);
      printf("\n\t\t\t\t_______________________________\n\n");
    }
  }

  if (!found) {
    printf("\n\t\tRecord not found\n");
  }
  fclose(fp);
}
void delete () {
  FILE *fp, *fp1;
  struct student info;
  int rollno, fileexist = 0;
  printf("\t\t\t\t======Delete Student======\n\n\n");
  fp = fopen("student_info.txt", "r");
  fp1 = fopen("temp.txt", "w");
  printf("\t\t\tEnter roll no: ");
  scanf("%d", &rollno);

  if (fp == NULL) {
    printf("Error opening file");
  }
  while (fread(&info, sizeof(struct student), 1, fp)) {
    if (info.rollno == rollno) {
      fileexist = 1;
    } else {
      fwrite(&info, sizeof(struct student), 1, fp1);
    }
  }
  fclose(fp);
  fclose(fp1);
  if (fileexist) {
    remove("student_info.txt");
    rename("temp.txt", "student_info.txt");
    printf("\n\t\t\tRecord deleted successfully\n");
  }
  if (!fileexist) {
    printf("\n\t\t\tRecord not found\n");
  }
}