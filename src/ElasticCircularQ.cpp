
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

ElasticCircularQ::~ElasticCircularQ()
{
	Release();
}

void ElasticCircularQ::Release()
{
	if (q)
		free(q);
	q = NULL;
}

ElasticCircularQ::ElasticCircularQ(size_ecq size_, size_ecq ex_)
{
	size = 0;
	ex = 0;
	n = 0;
	head = 0;
	tail = 0;
	HeadMovePending = 0;

	q = (void **)malloc(size_ * sizeof(void *));
	if (q)
	{
		size = size_;
		ex = ex_;
		memset(q, 0, sizeof(void *) * size);
	}
}

int ElasticCircularQ::IncreaseCapacity()
{
	int rc = 0;
	size_t ns = (size + ex) * sizeof(void *);
	int count = 0;

	if (ex < 1)
		return (-1);

	void **nvp = (void **)malloc(ns);
	if (nvp == NULL)
		return (-2);

	memset(nvp, 0, ns);

	// Copy msgs from old Q to new: the segment tail to end
	count = size - tail;
	count *= sizeof(void *);
	memcpy(nvp, q + tail, count);

	if (tail)
	{
		// Copy msgs from old Q to new: the segment begining to tail
		memcpy((unsigned char *)nvp + count, q, tail * sizeof(void *));
	}

	if (q)
	{
		free(q);
	}
	q = nvp;

	head = size;
	size += ex;
	tail = 0;
	HeadMovePending = 0;

	return (rc);
}

int ElasticCircularQ::Write(void *msg)
{
	int rc = -1;

	if (n < size) // Check whether Q has room or note.
	{
		if (HeadMovePending == 1) // Any pending task
		{
			// This block is only the completion of the pending task
			++head;
			HeadMovePending = 0;
			if (head == size)
				head = 0;
		}

		*(q + head) = msg; // Write the message to head.
		++n;			   // Increment the element count
		MoveHead();
		rc = 0;
	}
	else
	{
		// We need Q capacity increased
		if (IncreaseCapacity() == 0)
		{
			*(q + head) = msg; // Write the message to head.
			++n;			   // Increment the element count

			MoveHead();
			rc = 0;
		}
	}

	return (rc);
}

int ElasticCircularQ::MoveHead()
{
	if (n < size)
	{
		// We still have room in the Q to move the head
		++head;
		if (head == size)
			head = 0;
	}
	else
	{
		// head move is pending because Q is full right now
		// a Read operation could create room in the Q
		// if next operation is also write then we need capacity increase
		HeadMovePending = 1;
	}

	return (0);
}

void *ElasticCircularQ::Read()
{
	void *msg = NULL;

	if (n > 0) // Check it has any element.
	{
		msg = *(q + tail);  // Read the msg
		*(q + tail) = NULL; // erase the msg pointer stored.

		--n;
		++tail;
		if (tail == size)
		{
			tail = 0; // tail has exceeded the max size
		}
	}

	return (msg);
}

