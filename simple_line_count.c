#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char * parse_args(int argc, char * argv[]) {
	char * filename = NULL;
	size_t filename_len = 0;
	if (argc != 2) {
		fprintf(stderr, "[ERROR] Error in input arguments." \
			" Please type %s 'filename'\n", argv[0]);
		return NULL;
	}

	filename_len = strlen(argv[1]);
	filename = calloc(filename_len+1, 1);
	filename = memcpy(filename, argv[1], filename_len+1);
	filename[filename_len] = '\0';
	return filename;
}


int simple_count_lines(char * filename) {
	int c = 0;
	long unsigned int lines = 0;
	FILE * input_file = fopen(filename, "r");
	if (input_file == NULL) {
		fprintf(stderr, "[ERROR] Error while open file '%s'\n", filename);
		return -1;
	}


	while ((c = fgetc(input_file)) != EOF) {
		if (c == '\n')
			++lines;
	}

	// check error
	// exit from circle: EOF or error
	// for error detection see feof and ferror

	if (ferror(input_file) != 0) {
		fprintf(stderr, "[ERROR] Error while read file '%s'\n", filename);
		return -1;	
	}


	if (fclose(input_file) < 0) {
		fprintf(stderr, "[ERROR] Error while close file '%s'\n", filename);
		return -1;	
	}

	return lines;
}


int main(int argc, char * argv[]) {
	char * filename = NULL;
	long unsigned int lines = 0;

	filename = parse_args(argc, argv);
	if (filename == NULL)
		return 1;

	lines = simple_count_lines(filename);
	if (lines < 0)
		return 1;

	fprintf(stdout, "%lu %s\n", lines, filename);

	free(filename);
	return 0;
}
