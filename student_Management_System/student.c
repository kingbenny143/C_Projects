#include <stdio.h>
#include "student.h"

void addStudent(){
	struct student std;

	FILE* fout;

	fout = fopen("student.txt", "ab");
	if(fout==NULL) {
		printf("Error opening file");
	}
	else {
		printf("Enter student id:");
		scanf("%d",&std.id);

		printf("Enter student name:");
		scanf("%29s",std.name);

		printf("Enter student marks:");
		scanf("%f",&std.marks);

		fwrite(&std,sizeof(std),1,fout);
		fclose(fout);
	}
}

void viewStudent(){
	struct student std;
	FILE* fin;
	int sid, found = 0;

	fin = fopen("student.txt","rb");
	if(fin == NULL) {
		printf("Error opening file");
	}
	else {
		printf("Enter student id to view: ");
		scanf("%d",&sid);
		while (fread(&std, sizeof(std), 1, fin)) {
			if (sid == std.id) {
				found = 1;
				printf("student id:%d",std.id);
				printf("\nstudent name:%s",std.name);
				printf("\nstudent marks:%f",std.marks);
				break;
			}
		}
		
	}
	fclose(fin);
	if (found == 0) {
		printf("Student with is id %d not found", sid);
	}
}

void searchStudent(){
	struct student std;
	FILE* fin;
	int sid, found = 0;

	fin = fopen("student.txt", "rb");

	if (fin == NULL) {
		printf("Error opening file");
	}
	else {
		found = 1;
		printf("Enter student id to search: ");
		scanf("%d",&sid);
		while (fread(&std, sizeof(std), 1, fin)) {
			if (sid == std.id) {
				found = 1;
				printf("student id:%d",std.id);
				printf("\nstudent name:%s",std.name);
				printf("\nstudent marks:%f",std.marks);
			}
		}	
	}
	fclose(fin);
	if (found == 0) {
		printf("Student with is id %d not found", sid);
	}	
}

void updateStudent(){
	struct student std;
	int sid, found = 0;
	FILE* fout;
	FILE* fin;

	fin = fopen("student.txt", "rb");
	fout = fopen("temp.txt","ab");
	if(fin == NULL || fout == NULL) {
		printf("Error opening file");
	}
	else {
		printf("Enter student id to update: ");
		scanf("%d",&sid);
		while (fread(&std, sizeof(std), 1, fin)) {
			if (sid == std.id) {
				found = 1;
				printf("======Enter new student details======");
				printf("\nEnter student name: ");
				scanf("%29s", std.name);

				printf("\nEnter student marks: ");
				scanf("%f",&std.marks);
			}

			fwrite(&std, sizeof(std), 1, fout);
		}
	}
	fclose(fin);
	fclose(fout);

	if (found == 1) {
		remove("student.txt");
		rename("temp.txt","student.txt");
	}
	else {
		remove("temp.txt");
	}
}

void removeStudent(){
	struct student std;
	int sid, found = 0;
	FILE* fout;
	FILE* fin;

	fin = fopen("student.txt", "rb");
	fout = fopen("temp.txt","ab");
	if(fin == NULL || fout == NULL) {
		printf("Error opening file");
	}
	else {
		printf("Enter student id to update: ");
		scanf("%d",&sid);
		while (fread(&std, sizeof(std), 1, fin)) {
			if (sid != std.id) {
				fwrite(&std, sizeof(std), 1, fout);
			}
			else {
				found = 1;
			}
		}
	}
	fclose(fin);
	fclose(fout);
	if (found == 1) {
		remove("student.txt");
		rename("temp.txt","student.txt");
	}
	else {
		remove("temp.txt");
	}
}
