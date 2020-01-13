
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


#ifndef _ELASTIC_CIRCULAR_Q_
#define _ELASTIC_CIRCULAR_Q_

typedef unsigned int size_ecq;

class ElasticCircularQ
{
private:
	size_ecq size; // Initial Q capacity
	size_ecq ex;   // Q capacity expansion unit
	size_ecq head; // Next write index in the Q
	size_ecq tail; // Next read  index in the Q
	size_ecq n;	   // Number of element occupied
	void **q;	   // The Q base pointer
	char HeadMovePending;

public:
	ElasticCircularQ(size_ecq size_, size_ecq ex_);
	~ElasticCircularQ();
	void Release();
	void *Read();
	int Write(void *msg);

private:
	int IncreaseCapacity();
	int MoveHead();
};

#endif  // _ELASTIC_CIRCULAR_Q_

