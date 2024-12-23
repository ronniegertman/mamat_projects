#include "student.h"


struct student{
	char *name;
	int age;
	int id;
};

elem_t student_clone(elem_t this_student){
	struct student* src_student = (struct student*)this_student;
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
	strcpy(new_str, src_student->name);
	new_student->name = new_str;
	new_student->age = src_student->age;
	new_student->id = src_student->id;

	return (elem_t)new_student;
}

void student_destroy(elem_t this_student){
	free(((struct student*)this_student)->name);
	free((struct student*)this_student);
}

void student_print(elem_t this_student){
	struct student* student = (struct student*)this_student;
	printf("student name: %s, age: %d, id: %d\n",
			student->name, student->age, student->id);

}
