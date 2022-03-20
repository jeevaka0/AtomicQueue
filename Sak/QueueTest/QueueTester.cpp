/* Created by Jeevaka Dassanayake on 6/25/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "QueueTester.hpp"


QueueTester::QueueTester( SharedQueue& sharedQueue, unsigned long minSize, unsigned long maxSize, unsigned long numMessages )
		: sharedQueue( sharedQueue ), minSize( minSize ), maxSize( maxSize ), numMessages( numMessages ) {
	dataValue = 0;
}


void QueueTester::join() {
	pWorker->join();
}
