#include "student.h"



elem_t student_clone(elem_t this_student){
	//creating a new student object with the same fields as the cloned student
	struct student* src_student = (struct student*)this_student;
	//memory allocation for student object and student name
	struct student* new_student =
			(struct student*)malloc(sizeof(struct student));
	if (new_student == NULL){
		return NULL;
	}
	char* new_str = (char*)malloc(sizeof(src_student->name));
	if (new_str == NULL){
			free(new_student);
			return NULL;
		}
	//copying the fields
	strcpy(new_str, src_student->name);
	new_student->name = new_str;
	new_student->age = src_student->age;
	new_student->id = src_student->id;

	return (elem_t)new_student;
}

void student_destroy(elem_t this_student){
	//freeing the memory taken by given student
	free(((struct student*)this_student)->name);
	free((struct student*)this_student);
}

void student_print(elem_t this_student){
	//printing student fields
	struct student* student = (struct student*)this_student;
	printf("student name: %s, age: %d, id: %d\n",
			student->name, student->age, student->id);

}
