/* Created by Jeevaka Dassanayake on 6/25/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

class QueueReader : public QueueTester {
public :
	QueueReader( SharedQueue& sharedQueue, unsigned long minSize, unsigned long maxSize, unsigned long numMessages );
	virtual void start() override;
	virtual void join() override;
protected :
	// Typedefs


	// Methods
	void readData();
	const unsigned char* validatePartial( unsigned long size, const unsigned char* pData );
	void reportError( unsigned long read, unsigned long expected );

	// Data
};
