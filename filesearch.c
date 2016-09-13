// Author: Matthew Stephenson
// Date: 9/8/2016

#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main (int argc, char *argv[]) {
	if( argc < 3 ) {
		printf("Usage: search STRING FILE1 [FILE2 FILE3 ...]\n");
		return 0;
	}

	// For each file
	int i;
	for(i = 2; i < argc; i++) {
		//Initializing variables
		int lineNumber = 1;
		int charNum = 0;
		int foundStartPos = 0;
		int match = 0; // Treating as a boolean
		char *searchPtr = argv[1];
		int fd;

		int len = 10;
		char buffer[len];
		
		// Open the file
		if( (fd = open(argv[i], O_RDONLY)) < 0 ) {
			printf("Failed to open file '%s'\n", argv[i]);
			continue;
		}

		// Fill the buffer while number of characters read is > 0
		while( read(fd, &buffer, len) > 0 ) {
			int bufferIndex;

			for( bufferIndex = 0; bufferIndex < len; bufferIndex++, charNum++ ) {
				// If it's a newline character, increment lineNumber and reset character count
				if( buffer[bufferIndex] == '\n' ) {
					lineNumber++;
					charNum = 0;
				}
	
				// If a character match is found, then match is true, increment searchPtr. If not, reset variables.
				if( buffer[bufferIndex] == *searchPtr ) {
					match = 1;
					searchPtr++;
					
					if (foundStartPos < 1)
						foundStartPos = charNum;

				} else {
					match = 0;
					searchPtr = argv[1];
					foundStartPos = 0;
				}
			
				// If match is true and searchPtr is equal to the end of the search string, then we've found a match. Print line number. Reset searchPtr to beginning of search string and set match to false.
				if( match && searchPtr == (argv[2] - 1) ) {
					printf(message, "[%s]: Found '%s' at line %i, char %i\n", argv[i], argv[1], lineNumber, foundStartPos);
					match = 0;
					searchPtr = argv[1];
					foundStartPos = 0;
				}
			}
		}
		
		// Close the file
		close(fd);
	}

	return 0;
}
