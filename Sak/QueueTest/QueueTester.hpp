/* Created by Jeevaka Dassanayake on 6/25/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

class QueueTester {
public :
	QueueTester( SharedQueue& sharedQueue, unsigned long minSize, unsigned long maxSize, unsigned long numMessages );
	virtual void start() = 0;
	virtual void join();

protected :
	// Typedefs


	// Methods


	// Data
	SharedQueue& sharedQueue;
	unsigned long minSize;
	unsigned long maxSize;
	unsigned long numMessages;
	unsigned long dataValue;

	thread* pWorker;
};
