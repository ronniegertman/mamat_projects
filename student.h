#ifndef STUDENT_H
#define STUDENT_H
#include "stack.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string,h>

struct student;
elem_t student_clone(elem_t this_student);
void student_destroy(elem_t this_student);
void student_print(elem_t this_student);

#endif
