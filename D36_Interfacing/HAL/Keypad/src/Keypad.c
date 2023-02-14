/*
* Keypad.c
*
* Created: 10/1/2022 7:37:37 PM
*  Author: user
*/

#include "Keypad.h"

Uint8 KeyPadRow[4] = {r0,r1,r2,r3};
Uint8 KeyPadCol[4] = {c0,c1,c2,c3};
Uint8 KeyPad[4][4] = {{'7','8','9','/'},
					  {'4','5','6','*'},
					  {'1','2','3','-'},
					  {'C','0','=','+'}};

Uint8 GetKey(void){
	for (Uint8 w=0;w<4;w++)
	{
		DIO_WriteChannel(KeyPadRow[w],STD_High);//output 5v
		DIO_WriteChannel(KeyPadCol[w],STD_High);//Pull up Res.
	}
	for (Uint8 i=0;i<4;i++)
	{
		DIO_WriteChannel(KeyPadRow[i],STD_Low);
		for (Uint8 j=0;j<4;j++)
		{
			if (DIO_ReadChannel(KeyPadCol[j]) == STD_Low)
			{
				while(DIO_ReadChannel(KeyPadCol[j]) == STD_Low);
				return KeyPad[i][j];
			}
		}
		DIO_WriteChannel(KeyPadRow[i],STD_High);
	}
	return STD_Low;
}