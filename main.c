#include <stdio.h>
#include <stdlib.h>
// Set limit to line
#define LINE_BUFFER 1024

// Get length a string
unsigned int length(const char * str) {
    int count = 0;

    while (str[count] != '\0') count++;

    return count;
}

// Concatenate two strings to a target variable (dest)
int concat(const char * src_1, const char * src_2, char * dest, size_t sizeof_dest) {
    // Get lengths from sources
    unsigned int src_1_length = length(src_1);
    unsigned int src_2_length = length(src_2);
    // Calculate minimum length for dest
    unsigned int dst_length = src_1_length + src_2_length;

    if(sizeof_dest < dst_length)
        // Has no minimum length for concatenation
        return -1;

    int index = 0;
    for(int i = 0; i < src_1_length; i++) {
        index++;
        dest[i] = src_1[i];
    }
    for(int i = 0; i < src_2_length; i++) dest[index + i] = src_2[i];

    return 0;
}

// Read multiline
char * getCommand() {
    char * command = NULL;
    while(1) {
        char line[LINE_BUFFER];
        scanf("%[^\n]s", line);
        fflush(stdin);

        // Get line length
        unsigned int line_length = length(line);

        // Checking last character
        // zero - false
        // nonzero - true
        char has_slash = line[line_length - 1] == '\\' ? 1 : 0;

        // Update slash to breakline
        if(has_slash) line[line_length - 1] = '\n';

        if(command == NULL) {
            command = (char *) malloc(line_length * sizeof(char));
            // Copy line to command
            for(int i = 0; i < line_length; i++) command[i] = line[i];
        } else {
            // Concatenate command with current line for command update
            unsigned int command_length = length(command);
            unsigned int tmp_command_length = line_length + command_length;
            char tmp_command[tmp_command_length];
            if(concat(command, line, tmp_command, sizeof(tmp_command)) != 0) {
                printf("Error in concatenating '%s' with '%s'\n", command, line);
            }
            // Free memory from old command
            free(command);

            // Allocating memory for new updated command
            command = (char *) malloc(tmp_command_length * sizeof(char));
            // Copy command plus current line to new command
            for(int i = 0; i < tmp_command_length; i++) command[i] = tmp_command[i];
        }

        if(!has_slash) break;
    }

    return command;
}

int main() {
    char * command = getCommand();

    // Print result
    printf("\n---- BEGIN ---\n");
    printf("\n%s\n", command);
    printf("\n---- END ---\n");

    // Always clear data allocated in heap memory
    free(command);
    return 1;
}