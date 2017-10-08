
/*
 * Set 1 challenge 4
 */

#include "frequency_attack.h"

#include <stdio.h>



/*
 * Reads file with name 'fname'
 * Input
 *		fname: name of file to be read
 */
void read_file(char *fname) {
	/* 
	 * File format:
	 * 		line1
	 *		line2
	 *		... 60 lines
	 */

	char *line = (char *) malloc(sizeof(char) * 62);
	size_t size = 62;
	int read = 0;
	int counter = 1;
	char *res = NULL;
	int score = 0;

	FILE *fd = fopen(fname, "r");
	if (fd != NULL) {
		while ((read = getline(&line, &size ,fd)) != -1) {
			
			//printf("Counter = %i\n", counter);
			//printf("read: %i\n", read);
			line[read - 1] = '\0';
			//printf("%s\n",line);
			//printf("length = %i, length = %i, line: %s\n",read, size,line);

			if (counter) {
				res = do_attack(line);
				score = ascii_text_count(res, strlen(res));
				if ( score > strlen(res) * 0.8 * 4) {
					printf("Counter = %i\nScore = %i\n", counter, score);
					//dump_data(res, strlen(res), stdout);
					printf("%s\n", res);
				}

				free(res);
				res = NULL;

				//free(line);

				//size = 0;
				//line = NULL;
				
			}
			counter++;

			
		}
	}
}

void detect_single_char_xor(char fname) {




}


int main(int argc, char *argv[]) {
	
	/*
	 * ./setcha4 fname
	 */

	// Parse file name

	// Call detect_single_char_xor 

	read_file(argv[1]);

	return 0;
}