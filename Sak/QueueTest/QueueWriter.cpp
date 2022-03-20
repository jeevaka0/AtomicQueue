/* Created by Jeevaka Dassanayake on 6/25/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "QueueTester.hpp"
#include "QueueWriter.hpp"


QueueWriter::QueueWriter( SharedQueue& sharedQueue, unsigned long minSize, unsigned long maxSize, unsigned long numMessages)
		: QueueTester( sharedQueue, minSize, maxSize, numMessages ) {

}


void QueueWriter::start() {
	pWorker = new thread( &QueueWriter::writeData, this );
}


void QueueWriter::join() {
	QueueTester::join();
	cout << "Wrote " << numMessages << " messages." << endl;
}


void QueueWriter::writeData() {
	unsigned long i = 0;
	for ( ; i < numMessages; ++i ) {
		unsigned long size = minSize + i % ( maxSize - minSize + 1 );

		unsigned long* pData = (unsigned long*)sharedQueue.getTail();
		unsigned long* pEnd = pData + size / sizeof( unsigned long );
		while( pData < pEnd ) {
			*pData++ = dataValue;
		}
		sharedQueue.finishWrite( size );

		dataValue++;
	}
}
