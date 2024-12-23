#include <stdio.h>
#include <stdlib.h>

int count_lines(FILE *file);
int grade_in_range(int grade);
int compare(const void *a, const void *b);
int median(int *nums, int num_of_lines);
void handle_line(char* line, char* regex);

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

	char* regex = char*(malloc(sizeof(argv[2])));
	char line[256]; //buffer size string
	int i = 0;

//while to read each line in the file
	while(fgets(line, sizeof(line), file)){
		handle_line(line, regex);

	}
	fclose(file);
	free(regex);

	return 0;
}

void handle_line(char* line, char* regex){
	int i = 0;
	while(regex[i] != '\0'){

	}
}


