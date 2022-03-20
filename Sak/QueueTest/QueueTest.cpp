/* Created by Jeevaka Dassanayake on 6/24/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "../../StdPlus/StdPlus.hpp"

#include "../SakUtils.hpp"
#include "QueueTest.hpp"
#include "QueueTester.hpp"
#include "QueueReader.hpp"
#include "QueueWriter.hpp"


const SakUtils::TestMap QueueTest::members { { "rand", &QueueTest::randTest }
		, { "inc", &QueueTest::incTest }
		//, { "", &QueueTest:: }
		/*
			, { "", &QueueTest:: }
		*/
};


int QueueTest::test( int argc, char **argv, int index ) {
	return SakUtils::invoke( argc, argv, members, index );
}


// queue inc lines minMsgSize maxMsgSize numMessages
int QueueTest::incTest( int argc, char **argv, int index ) {
	if ( SakUtils::checkArgs( argc, argv, index, 4 ) ) {
		unsigned long messages = strtoul( argv[index++], nullptr, 10 );
		unsigned long minMsgSize = strtoul( argv[index++], nullptr, 10 );
		unsigned long maxMsgSize = strtoul( argv[index++], nullptr, 10 );
		unsigned long numMessages = strtoul( argv[index], nullptr, 10 );

		SharedQueue sharedQueue( messages, maxMsgSize );
		QueueReader reader( sharedQueue, minMsgSize, maxMsgSize, numMessages );
		QueueWriter writer( sharedQueue, minMsgSize, maxMsgSize, numMessages );

		writer.start();
		reader.start();
		reader.join();
		writer.join();

		cout << sharedQueue << endl;
	}

	return 0;
}


int QueueTest::randTest( int argc, char **argv, int index ) {



	return 0;
}
