#ifndef DRAND48_H
#define DRAND48_H

#include <stdlib.h>

#define m_drand 0x100000000LL
#define c_drand 0xB16
#define a_drand 0x5DEECE66DLL

static unsigned long long seed = 1;

double drand48(void)
{
	seed = (a_drand * seed + c_drand) & 0xFFFFFFFFFFFFLL;
	unsigned int x = seed >> 16;
	return 	((double)x / (double)m_drand);

}

void srand48(unsigned int i)
{
	seed = (((long long int)i) << 16) | rand();
}

#endif