/*--------------------------------------------------------------------*/
/* miniassembler.c                                                    */
/* Author: Bob Dondero, Donna Gabai                                   */
/*--------------------------------------------------------------------*/

#include "miniassembler.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

/*--------------------------------------------------------------------*/
/* Modify *puiDest in place,
   setting uiNumBits starting at uiDestStartBit (where 0 indicates
   the least significant bit) with bits taken from uiSrc,
   starting at uiSrcStartBit.
   uiSrcStartBit indicates the rightmost bit in the field.
   setField sets the appropriate bits in *puiDest to 1.
   setField never unsets any bits in *puiDest.                        */
static void setField(unsigned int uiSrc, unsigned int uiSrcStartBit,
                     unsigned int *puiDest, unsigned int uiDestStartBit,
                     unsigned int uiNumBits)
{
   unsigned int valSrc;
   
   /* left shifting and right shifting to get only uiNumBits starting 
      from the right at uiSrcStartBit*/
   valSrc = (((uiSrc>>uiSrcStartBit)<<(32-uiNumBits))>>(32-uiNumBits-uiSrcStartBit));

   /* leftshift or right shift the number of bits required to get the 
      appropriate vits to start at position uiDestStartBit. */
   if(uiDestStartBit>uiSrcStartBit)
      valSrc = valSrc<<(uiDestStartBit-uiSrcStartBit);
   else
      valSrc = valSrc>>(uiDestStartBit-uiSrcStartBit);
   
   /* maintain the 1's in puiDest while setting only the 1's in valSrc 
      equal to the respective position in puiDest. */
   *puiDest = *puiDest | valSrc;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_mov(unsigned int uiReg, int iImmed)
{
   unsigned int uiInstr;
   /* base instruction code */
   uiInstr = 0x52800000;

   /* destination register */
   setField(uiReg, 0, &uiInstr, 0,5);

   /* value to be placed in register */
   setField(iImmed, 0, &uiInstr, 5,16);
   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_adr(unsigned int uiReg, unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;

   /* Base Instruction Code */
   uiInstr = 0x10000000;

   /* register to be inserted in instruction */
   setField(uiReg, 0, &uiInstr, 0, 5);

   /* displacement to be split into immlo and immhi and inserted */
   uiDisp = (unsigned int)(ulAddr - ulAddrOfThisInstr);

   setField(uiDisp, 0, &uiInstr, 29, 2);
   setField(uiDisp, 2, &uiInstr, 5, 19);

   return uiInstr;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_strb(unsigned int uiFromReg,
   unsigned int uiToReg)
{
   unsigned int ret = 0x39000000;
   setField(uiToReg, 0, &ret, 5,5);
   setField(uiFromReg, 0, &ret, 0,5);   
   return ret;
}

/*--------------------------------------------------------------------*/

unsigned int MiniAssembler_b(unsigned long ulAddr,
   unsigned long ulAddrOfThisInstr)
{
   unsigned int uiInstr;
   unsigned int uiDisp;
   /* Base Instruction Code */
   uiInstr = 0x14000000;

   /* address offset between ulAddr and ulAddrOfThisInstr */
   uiDisp = (unsigned int)(ulAddr-ulAddrOfThisInstr)/4;

   /* setting the appropriate fields with the address offset */
   setField(uiDisp, 0, &uiInstr, 0, 26);
   return uiInstr; 
}

