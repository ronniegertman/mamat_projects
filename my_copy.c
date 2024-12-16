#include <stdio.h>
#include <stdlib.h>

int count_lines(FILE *file);
int grade_in_range(int grade);
int compare(const void *a, const void *b);
int median(int *nums, int num_of_lines);

int main(int argc, char **argv) {
// we assume that argv[1] is the path
	//checking if a path was specified, if not, we use stdin
	FILE *file;
	if (argv[1] == NULL || *argv[1] == '-'){
		file = stdin;
	} else{
		file = fopen(argv[1], "r");
	}

	if (file == NULL){
		return(1);
	}

	//allocating memory for the grades array
	int num_of_lines = count_lines(file);
	int* nums_array = (int *)malloc(num_of_lines * sizeof(int));
	rewind(file);

	if (nums_array == NULL){
		return (1);
	}



	char line[40]; //buffer size string
	int i = 0;

//while to read each line in the file
	while(fgets(line, sizeof(line), file)){
		int num = atoi(line); //convert from string to int

		//checking if grade is in range
		if (!grade_in_range(num)){
			fprintf(stderr, "Error at line %d: invalid input %d\n", i+1, num);
			return(1);
		}

		//adding to array if in range
		nums_array[i] = num;
		i++;
	}
	printf("num of lines %d\n", num_of_lines);

	fprintf(stdout, "%d\n", median(nums_array, num_of_lines));

	free(nums_array);
	fclose(file);

	return 0;
}

//wait is size of line????
int count_lines(FILE *file){
	//calculating amount of lines in a file, assuming it contains only integers
	int lines = 0;
	char line[40];
	while (fgets(line, sizeof(line), file)){
		lines ++;
	}
	return lines;
}

int grade_in_range(int grade){
	//checking if the grade is real lol
	return grade >= 0 && grade <= 100;
}

int compare(const void *a, const void *b){
	//comparison function for qsort
	return (*(int *)a - *(int *)b);
}

int median(int *nums, int num_of_lines){
	//calculating the median grade
	qsort(nums, num_of_lines, sizeof(nums[0]), compare);
	return nums[(num_of_lines + 1)/2 - 1];
}
