#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>

struct grade_list_element{
	int grade;
	char* name;
};

struct student_list_element{
	int id;
	char* name;
	struct list* grades;
};

struct grades{
	struct list* students;
	size_t size;
};


//int clone_grade(void *element, void **output){
//	int* grade = (int *)element;
//	*(int* )output = (int *)malloc(sizeof(int));
//	if(*output == NULL){
//		return 1;
//	}
//	**output = *grade;
//	return 0;
//}

int clone_grade(void *element, void **output){
	if(element == NULL || output == NULL){
		return 1;
	}
	struct grade_list_element* grade = (int *)element;
	*output = malloc(sizeof(int)); // Allocate memory for an integer
	if (*output == NULL) {
	    return 1; // Handle memory allocation failure
	}
	*(int *)(*output) = *grade; // Copy the value from grade to the allocated memory
	return 0; // Success
}

void destroy_grade(void* element){
	//clones an element - a grade in a list of grades
	int* grade = (int* )element;
	free(grade);
}

struct list* clone_grade_list(struct list *list){
	//clones list of grades
	if(list == NULL){
		return NULL;
	}
	struct list *cloned_list = list_init(clone_grade, destroy_grade);
	if(cloned_list == NULL){
		return NULL;
	}
	struct iterator* tmp = list_begin(list);
	while(tmp != NULL){
		int* grade = list_get(tmp);
		int res = list_push_back(cloned_list, (void *)grade);
		if (res == 1){
			list_destroy(cloned_list);
			return NULL;
		}
		tmp = list_next(tmp);
	}
	return cloned_list;
}

void* clone_student(void* element){
	//clones an element - a student in a list of students
	if (element == NULL){
		return NULL;
	}
	struct student_list_element* student =
			(struct student_list_element*)element;
	//student element has a field which is a list, we need to clone this
	//entire list using the clone list function created above
	struct list* copied_grades = clone_grade_list(student->grades);
	if(copied_grades == NULL){
		return NULL;
	}
	if(student->name == NULL){
		list_destroy(copied_grades);
		return NULL;
	}
	char* copied_name = (char *)malloc(sizeof(student->name));
	if(copied_name == NULL){
		list_destroy(copied_grades);
		return NULL;
	}
	strcpy(copied_name, student->name);

	struct student_list_element* new_student =
			(struct student_list_element*)
			malloc(sizeof(struct student_list_element));
	if(new_student == NULL){
		free(copied_name);
		list_destroy(copied_grades);
		return NULL;
	}
	new_student->grades = copied_grades;
	new_student->name = copied_name;
	new_student->id = student->id;
	return (void*)new_student;
}

void destroy_student(void* element){
	struct student_list_element* student =
				(struct student_list_element*)element;
	list_destroy(student->grades);
	free(student->name);
	free(student);
}

struct grades* grades_init(){
	struct grades* new_grades = (struct grades*)malloc(sizeof(struct grades));
	if(new_grades == NULL){
		return NULL;
	}
	new_grades->size = 0;
	struct list* new_students = list_init(clone_student, destroy_student);
	if(new_students == NULL){
		free(new_grades);
		return NULL;
	}
	new_grades->students = new_students;
	return new_grades;
}

//we need to do clone and destroy user functions both for:
//a single grade, student list element
//in clone and destroy of student list element we need
//to call for clone and destroy of grades

void grades_destroy(struct grades *grades){
	list_destroy(grades->students);
	free(grades);
}

int grades_find_id(struct grades *grades, int id){
	struct list* list = grades->students;
	struct iterator* tmp = list_begin(list);
	while(tmp != NULL){
		struct student_list_element* student = list_get(tmp);
		if (student->id == id){
			return 0;
		}
		tmp = list_next(tmp);
	}
	return 1;
}

int grades_add_student(struct grades *grades, const char *name, int id){
	if(grades == NULL || grades_find_id(grades, id) == 0){
		return 1;
	}
	struct student_list_element* new_student;
	new_student->id = id;
	char* copied_name = (char *)malloc(sizeof(name));
		if(copied_name == NULL){
			return 1;
		}
	strcpy(copied_name, name);
	new_student->grades = list_init(clone_grade, destroy_grade);
	if (new_student->grades == NULL){
		free(copied_name);
		return 1;
	}
	new_student->name = copied_name;
	if (list_push_back(grades->students,new_student) == 1){
		free(copied_name);
		list_destroy(new_student->grades);
		return 1;
	}
	grades->size++;
	return 0;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

}
