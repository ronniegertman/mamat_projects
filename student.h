#ifndef STUDENT_H
#define STUDENT_H
#include "common.h"
#include <string.h>

struct student {
    int id;
    char *name;
    int age;
};
elem_t student_clone(elem_t this_student);
void student_destroy(elem_t this_student);
void student_print(elem_t this_student);

#endif
