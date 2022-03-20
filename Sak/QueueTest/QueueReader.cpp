/* Created by Jeevaka Dassanayake on 6/25/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "QueueTester.hpp"
#include "QueueReader.hpp"


QueueReader::QueueReader( SharedQueue& sharedQueue, unsigned long minSize, unsigned long maxSize, unsigned long numMessages )
		: QueueTester( sharedQueue, minSize, maxSize, numMessages ) {

}


void QueueReader::start() {
	pWorker = new thread( &QueueReader::readData, this );
}


void QueueReader::join() {
	QueueTester::join();
	cout << "Read " << numMessages << " messages." << endl;
}


void QueueReader::readData() {
	unsigned long i = 0;
	for ( ; i < numMessages; ++i ) {
		unsigned long size;
		unsigned long* pData = (unsigned long*)sharedQueue.getHead( size );
		unsigned long* pEnd = pData + size / sizeof( unsigned long );

		// Validations.
		if ( size < minSize || maxSize < size ) {
			cerr << "Message size " << size << " outside range [" << minSize << "," << maxSize << "]" << endl;
			throw size;
		}

		while( pData < pEnd ) {
			if ( dataValue != *pData ) {
				reportError( *pData, dataValue );
			}
			pData++;
		};
		sharedQueue.finishRead();
		dataValue++;
	}
}


void QueueReader::reportError( unsigned long read, unsigned long expected ) {
	cerr << "Value read: " << hex << read << ", expected: " << hex << expected << endl;
	// Add reader and queue print functions and stream out details.
	throw read;
}
