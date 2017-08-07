#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

// TODO Add long arithmetic
// may be array or dynamic array of char


// file size restriction -> https://en.wikipedia.org/wiki/Comparison_of_file_systems


// Можно сначала складывать все в long unsigned int, когда переменная
// переполнится, то складывать уже со строкой

// Кроме этого можно работать с массивом байт не как со строкой, а
// а как с массивом 4-битовых чисел. Таким образом можно сократить
// объем используемой памяти в два раза


void print_convert_string(char * number) {
	if (number == NULL) {
		printf("empty string\n");
		return;
	}

	long unsigned int number_len = strlen(number);
	long int i = number_len - 1;

	while (i >= 1) {
		if (number[i] != '0')
			break;

		--i;
	}
	
	for (; i >= 1; --i)
		putchar(number[i]);

	putchar(number[0]);
}


char * parse_args(int argc, char * argv[]) {
	char * filename = NULL;
	size_t filename_len = 0;
	if (argc != 2) {
		fprintf(stderr, "[ERROR] Error in input arguments." \
			" Please type %s 'filename'\n", argv[0]);
		return NULL;
	}

	filename_len = strlen(argv[1]);
	filename = calloc(1, filename_len+1);
	filename = memcpy(filename, argv[1], filename_len+1);
	filename[filename_len] = '\0';
	return filename;
}


// TODO write this function

// Использовать строку не получится, так как
// по ней по-любому нужно будет пробегать, а для этого
// понадобится индекс (он ограничен 2^64, 8 байтами)
// Строка - хороший вариант. Так как длина числа максимального
// будет больше 10^19 соответственно само число -> 10^(10^19)

// Нужно скорее всего сделать однонаправленный список, в котором 
// хранить значение отдельной цифры. Пробегать по списку можно при
// помощи while, концом будет next == NULL


char * increment_str_num(char * number) {
	int c = 0; 
	char * result;
	int delta = 10;
	int overflow = 1;
	long unsigned int curr_pos = 0;
	long unsigned int number_len = 0;
	
	if (number == NULL) {
		result = calloc(2, 1);
		result[0] = '0';
		result[1] = '\0';
		++number_len;
	} else {
		number_len = strlen(number);
		result = number;
	}

	c = result[0];

	while (c != '\0') {
		if (isdigit(c) == 0) {
			fprintf(stderr, "[ERROR] Error while increment number '%s'\n", result);
			free(result);
			return NULL;
		}

		unsigned short digit = c - '0';
		
		if (overflow == 0)
			break;

		if (++digit == 10) {
			result[curr_pos] = '0';
		} else {
			result[curr_pos] = (char)(c + 1);
			overflow = 0;
		}

		++curr_pos;
		c = result[curr_pos];
	}

	if (overflow == 1) {
		char * new_number = realloc(result, number_len + 1 + delta);
		if (new_number == NULL) {
			fprintf(stderr, "[ERROR] Error while allocate memory for number\n");
			free(result);
			return NULL;
		}

		result = new_number;

		result[number_len] = '1';
		result[number_len + delta] = '\0';

		for (int i = 1; i < delta; ++i)
			result[number_len + i] = '0';

		number_len = number_len + delta;
	}

	return result;

}


char * count_lines(char * filename) {
	int c = 0;
	
	char * lines = NULL;
	char * result = NULL;
	lines = calloc(2, 1);
	lines[0] = '0';
	lines[1] = '\0';

	FILE * input_file = fopen(filename, "r");
	if (input_file == NULL) {
		fprintf(stderr, "[ERROR] Error while open file '%s'\n", filename);
		return NULL;
	}

	while ((c = fgetc(input_file)) != EOF) {
		if (c == '\n') {
			result = increment_str_num(lines);
			if (result == NULL) {
				fprintf(stderr, "[ERROR] Error while incrementing lines in '%s'\n", filename);
				return NULL;
			}
			lines = result;
		}
	}

	// check error
	// exit from circle: EOF or error
	// for error detection see feof and ferror

	if (ferror(input_file) != 0) {
		fprintf(stderr, "[ERROR] Error while read file '%s'\n", filename);
		return NULL;	
	}


	if (fclose(input_file) < 0) {
		fprintf(stderr, "[ERROR] Error while close file '%s'\n", filename);
		return NULL;	
	}

	return lines;
}


int main(int argc, char * argv[]) {
	char * filename = NULL;
	char * lines_number = NULL;

	filename = parse_args(argc, argv);
	if (filename == NULL)
		return 1;

	lines_number = count_lines(filename);
	if (lines_number == NULL) {
		fprintf(stderr, "[ERROR] Error while counting lines in '%s'\n", filename);	
		return 1;
	}

	print_convert_string(lines_number);
	fprintf(stdout, " %s\n", filename);
	
	free(lines_number);
	free(filename);
	
	return 0;
}
