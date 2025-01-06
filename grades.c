#include "grades.h"
#include "linked-list.h"
#include <stdlib.h>
#include <string.h>

struct grade_list_element{
	int grade;
	char* course_name;
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
	//clones a grade list element
	if(element == NULL || output == NULL){
		return 1;
	}
	//casting
	struct grade_list_element* grade_element =
			(struct grade_list_element*)element;
	//creating a new element
	struct grade_list_element* new_grade =
			(struct grade_list_element *)
			malloc(sizeof(struct grade_list_element));
	if (new_grade == NULL) {
	    return 1; // Handle memory allocation failure
	}

	//copying the name using memory allocation
	char* copied_name = (char *)malloc(sizeof(grade_element->course_name));
		if(copied_name == NULL){
			free(new_grade);
			return 1;
		}
	strcpy(copied_name, grade_element->course_name);
	new_grade->course_name = copied_name;
	new_grade->grade = grade_element->grade;

	//casting new element to output
	*(struct grade_list_element*)(*output) = *new_grade;
	return 0; // Success
}

void destroy_grade(void* element){
	//destroying memory allocated for course name, and struct
	struct grade_list_element* grade = (struct grade_list_element*)element;
	free(grade->course_name);
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
	//iterating through list, getting each element of the list
	//adding a clone of this element to the new list
	struct iterator* tmp = list_begin(list);
	while(tmp != NULL){
		struct grade_list_element* grade = list_get(tmp);
		int res = list_push_back(cloned_list, (void *)grade);
		if (res == 1){
			list_destroy(cloned_list);
			return NULL;
		}
		tmp = list_next(tmp);
	}
	return cloned_list;
}

int clone_student(void* element, void** output){
	//clones an element - a student in a list of students
	if (element == NULL){
		return 1;
	}
	//casting
	struct student_list_element* student =
			(struct student_list_element*)element;

	//student element has a field which is a list, we need to clone this
	//entire list using the clone list function created above
	struct list* copied_grades = clone_grade_list(student->grades);
	if(copied_grades == NULL){
		return 1;
	}
	if(student->name == NULL){
		list_destroy(copied_grades);
		return 1;
	}
	//copying the name - memory allocation
	char* copied_name = (char *)malloc(sizeof(student->name));
	if(copied_name == NULL){
		list_destroy(copied_grades);
		return 1;
	}
	strcpy(copied_name, student->name);

	//creating a new student element
	struct student_list_element* new_student =
			(struct student_list_element*)
			malloc(sizeof(struct student_list_element));
	if(new_student == NULL){
		free(copied_name);
		list_destroy(copied_grades);
		return 1;
	}
	//copying all the fields
	new_student->grades = copied_grades;
	new_student->name = copied_name;
	new_student->id = student->id;
	*(struct student_list_element*)(*output) = *new_student;
	return 0; // Success
}

void destroy_student(void* element){
	struct student_list_element* student =
				(struct student_list_element*)element;
	list_destroy(student->grades);
	free(student->name);
	free(student);
}

struct grades* grades_init(){
	//creating a new struct
	struct grades* new_grades = (struct grades*)malloc(sizeof(struct grades));
	if(new_grades == NULL){
		return NULL;
	}
	//initializing size
	new_grades->size = 0;
	//creating an empty list of students
	struct list* new_students = list_init(clone_student, destroy_student);
	if(new_students == NULL){
		free(new_grades);
		return NULL;
	}
	new_grades->students = new_students;
	return new_grades;
}

void grades_destroy(struct grades *grades){
	//freeing allocated memory for the list and for the struct
	list_destroy(grades->students);
	free(grades);
}

struct student_list_element* grades_find_id(struct grades *grades, int id){
	struct list* list = grades->students;
	struct iterator* tmp = list_begin(list);
	while(tmp != NULL){
		struct student_list_element* student = list_get(tmp);
		if (student->id == id){
			return student;
		}
		tmp = list_next(tmp);
	}
	//we couldn't find a student with given id
	return NULL;
}

int grades_add_student(struct grades *grades, const char *name, int id){
	if(grades == NULL || grades_find_id(grades, id) != NULL){
		return 1;
	}
	//no need to allocate memory for the student because
	//list push clones the element
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
	//trying to add the student to the grades struct
	if (list_push_back(grades->students,new_student) == 1){
		free(copied_name);
		list_destroy(new_student->grades);
		return 1;
	}
	grades->size++;
	//freeing aloucated memory that got cloned
	free(copied_name);
	return 0;
}

int grades_find_course_name(struct student_list_element* student, char* name){
	struct list* list = student->grades;
	struct iterator* tmp = list_begin(list);
	while(tmp != NULL){
		struct grade_list_element* grade = list_get(tmp);
		if (strcmp(grade->course_name, name)){
			return 0;
		}
		tmp = list_next(tmp);
	}
	//we couldn't find this course name
	return 1;
}

int grades_add_grade(struct grades *grades,
                     const char *name,
                     int id,
                     int grade){

	struct student_list_element* student = grades_find_id(grades, id);
	if(grades == NULL || student == NULL){
		return 1;
	}
	if(grade < 0 || grade > 100 ||
			grades_find_course_name(student, name) == 1){
			return 1;
		}
	struct grade_list_element* new_grade;
	new_grade->grade = grade;
	char* copied_name = (char *)malloc(sizeof(name));
			if(copied_name == NULL){
				return 1;
			}
	strcpy(copied_name, name);
	new_grade->course_name = copied_name;

	if (list_push_back(student->grades,new_grade) == 1){
			free(copied_name);
			return 1;
		}
	//freeing allocated memory that got cloned
	free(copied_name);
	return 0; //Success
}

float grades_calc_avg(struct grades *grades, int id, char **out){
	struct student_list_element* student = grades_find_id(grades, id);
	// setting the out to NULL as default, if all goes well it will be changed
	out = NULL;
	if(grades == NULL || student == NULL){
		return -1;
	}
	//no courses
	if(list_size(student->grades) == 0){
		return 0;
	}
	struct list* list = student->grades;
	struct iterator* tmp = list_begin(list);
	//calculating average
	int sum = 0;
	while(tmp != NULL){
		struct grade_list_element* grade = list_get(tmp);
		sum += grade->grade;
		tmp = list_next(tmp);
	}

	//setting the output to the student's name
	char* copied_name = (char *)malloc(sizeof(student->name));
	if(copied_name == NULL){
		return -1;
	}
	strcpy(copied_name, student->name);
	*out = copied_name;

	return (float)(sum/list_size(list));
}

int grades_print_student(struct grades *grades, int id){
	struct student_list_element* student = grades_find_id(grades, id);
	if(grades == NULL || student == NULL){
		return 1;
	}
	printf("%s %d: ", student->name, student->id);
	struct list* list = student->grades;
	if(list_size(list) == 0){
		printf("\n");
		return 0;
	}
	struct iterator* tmp = list_begin(list);
	//we will print the first grade manually because of the lack of a comma
	struct grade_list_element* first_grade = list_get(tmp);
	printf("%s %d", first_grade->course_name, first_grade->grade);
	tmp = list_next(tmp);
	while(tmp != NULL){
		struct grade_list_element* grade = list_get(tmp);
		printf(", %s %d", grade->course_name, grade->grade);
		tmp = list_next(tmp);
	}
	printf("\n");
	return 0; //Success
}

int grades_print_all(struct grades *grades){
	if(grades == NULL){
		return 1;
	}
	struct list* list = grades->students;
	//checking if there are any students
	if(list_size(list) == 0){
		return 0;
	}
	struct iterator* tmp = list_begin(list);
	while(tmp != NULL){
		struct student_list_element* student = list_get(tmp);
		//printing student details
		grades_print_student(grades, student->id);
		tmp = list_next(tmp);
	}
	return 0; //Success

}

