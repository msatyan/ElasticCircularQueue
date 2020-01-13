/*
MIT License

Copyright (c) 2020 Sathyanesh Krishnan

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "ElasticCircularQ.h"

int Test_ecq(int size, int ex, int r, int maxQelements);

int main()
{
	int rc = 0;
	int i = 0;
	int TestID = 0;
	int MaxIteration = 15;

	int maxQelements = 0; // Try to add this many items to the Q
	int size = 0;		  // Initial Q capacity
	int ex = 0;			  // Q capacity expansion unit
	int r = 0;			  // Read from Q when no reminder to iteration count.

	TestID = 0;
	for (i = 1; i <= MaxIteration; ++i)
	{
		maxQelements = i * 10000;
		size = i * 128;
		ex = i * 32;

		r = i % 10;
		if (r < 2)
			r = 2;

		if ((rc = Test_ecq(size, ex, r, maxQelements)) == 0)
		{
			printf("\nTest-%d PASSED: size=%d,   ex=%d,   r=%d,   maxQelements=%d", ++TestID, size, ex, r, maxQelements);
		}
		else
		{
			printf("\nTest-%d FAILED: size=%d,   ex=%d,   r=%d,   maxQelements=%d", ++TestID, size, ex, r, maxQelements);
		}
	}
	printf("\n\n");
}


int Test_ecq(int size, int ex, int r, int maxQelements)
{
	const int msg_buff_size = 64;
	char exp_val[msg_buff_size];
	const char *msg_template = "Test msg %d";

	char *msg = NULL;
	int exp_tag = -1;
	int i = 0;
	int rc = 0;

	ElasticCircularQ ecq(size, ex);

	for (i = 0; i < maxQelements; ++i)
	{
		if ( (msg=(char *)malloc(msg_buff_size)) == NULL)
		{
			printf("\nMemory allocation error");
			exit(1);
		}

		sprintf(msg, msg_template, i);

		if (ecq.Write(msg) != 0)
		{
			printf("\n Write failed : i=%d]", i);
		}

		if (i % r == 0)
		{
			msg = (char *)ecq.Read();
			sprintf(exp_val, msg_template, ++exp_tag);
			if (strcmp(msg, exp_val) != 0)
			{
				rc = 1;
				printf("\n #: exp=[%s],  msg=[%s]", exp_val, msg);
			}

			free(msg);
		}
	}

	// Starting the Q deallocation process
	while (true)
	{
		msg = (char *)ecq.Read();
		if (msg == NULL)
		{
			break;
		}

		sprintf(exp_val, msg_template, ++exp_tag);
		if (strcmp(msg, exp_val) != 0)
		{
			rc = 1;
			printf("\n x: exp=[%s],  msg=[%s]", exp_val, msg);
		}

		free(msg);
	}

	ecq.Release();
	return (rc);
}
