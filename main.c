/*
 * main.c
 *
 *  Created on: Mar 29, 2016
 *      Author: Dimas Widyasastrena
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <strings.h>


int binRes[10];
int iteration = 0;

int16_t test;
int32_t alt;
//int gillCode;

int* conv2Bin(int num)
{
	int rem;

	rem = num;

	while( rem != 0)
	{
		binRes[++iteration] = rem % 2;
		rem /= 2;
	}
	return binRes;
}

void conv2Gillham(int* bin)
{
	int i;
	int gillCode[iteration];

	gillCode[0] = bin[iteration];
	for(i = 1; i <= iteration; i++)
	{
		gillCode[i] = bin[i] ^ bin[i+1];
	}

	for(i = iteration; i > 0; i--)
	{
		printf("%d", gillCode[i]);
	}
}


uint32_t Gray2Bin(int gill)
{
	uint32_t temp;

	temp = gill ^ (gill >> 8);

	temp ^= (temp >> 8);
	temp ^= (temp >> 4);
	temp ^= (temp >> 2);
	temp ^= (temp >> 1);

	return temp;
}

int32_t Gillham2Alt(int16_t code)
{
	int16_t fiveHundreds;
	int16_t oneHundreds;

	int32_t gillCode;

	fiveHundreds = code >> 3;
	oneHundreds  = code & 0x07;

	fiveHundreds = Gray2Bin(fiveHundreds);
	oneHundreds  = Gray2Bin(oneHundreds);

	if(oneHundreds == 5 || oneHundreds == 6 || oneHundreds == 0)
	{
		gillCode = -9;

		return gillCode;
	}

	if(oneHundreds == 7)
	{
		oneHundreds = 5;
	}

	if(fiveHundreds % 2)
	{
		oneHundreds = 6 - oneHundreds;
	}

	gillCode = (int32_t)((fiveHundreds * 500) + (oneHundreds * 100)) - 1300;

	return gillCode;
}

int main()
{
	char tmp[12];

	int i = 0;
	int decimal = 0;

	printf("Enter Code (D1 D2 D4 A1 A2 A4 B1 B2 B4 C1 C2 C4) : ");
	gets(tmp);

/*
	int i;
	conv2Bin(test);
	for(i = iteration; i > 0; i--)
	{
		printf("%d", binRes[i]);
	}

	printf("Gray code for %d is ", test);
	conv2Gillham(conv2Bin(test));
*/

	while(tmp[i] != '\0')
	{
		if(tmp[i] == '1')
			decimal = decimal * 2 + 1;
		else if(tmp[i] == '0')
			decimal *= 2;
		i++;
	}

	//printf("%s\n", tmp);
	alt = Gillham2Alt(decimal);
	printf("Resulting an altitude of %d in feet", alt);

	return 0;
}
