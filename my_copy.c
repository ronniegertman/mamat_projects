#include <stdio.h>
#include <stdlib.h>

void file_copy(FILE *src, FILE *dest);

int main(int argc, char **argv) {
// we assume that argv[1] is the path
	//checking if a path was specified, if not, we use stdin
	FILE *file_src;
	FILE *file_dest;
	if (*argv[1] == '-'){
		file_src = stdin;
	} else{
		file_src = fopen(argv[1], "r");
	}

	if (*argv[2] == '-'){
		file_dest = stdout;
	} else{
		file_dest = fopen(argv[2], "w");
	}


	if (file_src == NULL || file_dest == NULL){
		fprintf(stderr, "Error occurred\n");
		return(1);
	}
	file_copy (file_src, file_dest);
	fclose(file_src);
	fclose(file_dest);

	return 0;
}



void file_copy(FILE *src, FILE *dest){
	char buffer[2];
	while (fgets(buffer, sizeof(buffer), src)){
		fwrite(buffer, sizeof(char), 1, dest);
	}
	rewind(src);
	rewind(dest);


}


