#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"

// DIRECTIONS
//    implement loadFile2D, substringSearch2D, and free2D.

#define INITIAL_CAPACITY 10
#define LINE_LENGTH 100
#define COLS 100

// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).
char (*loadFile2D(char *filename, int *size))[COLS]
{
	FILE *in = fopen(filename, "r");
	if (!in) {
	    perror("Can't open file");
	    exit(1);
	}
	
	// TODO
	// Allocate memory for an 2D array, using COLS as the width.
	int capacity = INITIAL_CAPACITY;
	*size = 0;
	char (*arr)[COLS] = malloc(capacity * sizeof(*arr));
	if (!arr) {
		perror("Memory allocation failed");
		fclose(in);
		exit(1);
	}

	// Read the file line by line into a buffer.
	char buffer[LINE_LENGTH];
	while (fgets(buffer, sizeof(buffer), in)) {
		//   Trim newline.
		buffer[strcspn(buffer, "\n")] = '\0';
		//   Expand array if necessary (realloc).
		if (*size >= capacity) {
			capacity *= 2;
			char (*tmp)[COLS] = realloc(arr, capacity * sizeof(*arr));
			if (!tmp) {
				perror("Memory reallocation failed.");
				free(arr);
				fclose(in);
				exit(1);
			}
			arr = tmp;
		}
		//   Copy each line from the buffer into the array (use strcpy).
		strncpy(arr[*size], buffer, COLS - 1);
		arr[*size][COLS -1] = '\0';
		(*size)++; // Size is updated here instead so it stays inside the loop.
	}
    
    // Close the file.
	fclose(in);
	// The size should be the number of entries in the array.
	//*size = 0;
	
	// Return pointer to the array.
	return arr;
}

// Search the array for the target string.
// Return the found string or NULL if not found.
char * substringSearch2D(char *target, char (*lines)[COLS], int size)
{
    for (int i = 0; i < size; i++) {
		if (strstr(lines[i], target) != NULL) {
			return lines[i];
		}
	}
    return NULL;
}

// Free the memory used by the array
void free2D(char (*arr)[COLS]) {
	free(arr);
}
