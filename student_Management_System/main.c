#include<stdio.h>
#include "student.h"
int main(){
	int choice;
	
	while(1){
		printf("\n===== STUDENT MANAGEMENT SYSTEM =====");
		printf("\n1. Add Student\n2. View Students\n3. Search Student\n4. Update Student\n5. Delete Student\n6. Exit\nEnter your choice: ");
		scanf("%d", &choice);
		
		//FILE*
		if(choice == 1) {
			addStudent();
		}
		else if(choice == 2) {
			viewStudent();
		}
		else if(choice == 3) {
			searchStudent();
		}
		else if(choice == 4) {
			updateStudent();
		}
		else if(choice == 5) {
			removeStudent();
		}
		else if(choice == 6) {
			break;
		}
	}
	
	
}
