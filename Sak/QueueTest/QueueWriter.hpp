/* Created by Jeevaka Dassanayake on 6/25/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

class QueueWriter : public QueueTester {
public :
	QueueWriter( SharedQueue& sharedQueue, unsigned long minSize, unsigned long maxSize, unsigned long numMessages );
	virtual void start() override;
	virtual void join() override;
protected :
	// Typedefs


	// Methods
	void writeData();

	// Data
};
