/* Created by Jeevaka Dassanayake on 6/24/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

#include "../../Shared/BaseIncludes.hpp"
#include "SharedQueue.hpp"

using namespace StdPlus;

/* Notes:
 * A. We keep messages in contiguous blocks to allow the client to read messages without caring about queue wrapping.
 * B. Reader thread assumes next message is available if the 'size' in the header of the next message is non-zero. The writer
 * thread is responsible for making it 0 before writing the 'size' of the previous message.
 */


/* *1: To allow 'A' above, we don't start a new message at the end of the memory block when it has less than
 * maxMessageLines slots. The read pointer will move to the start of the memory block after reading the previous message,
 * skipping at most 'maxMessageLines - 1' slots. Due to 'B', this should be marked empty (size=0) when before the writer
 * makes the previous message available. I.e. we need extra 'maxMessageLines' lines to guarantee that the queue can contain
 * 'message' number or 'maxMessageSize' messages.
 */



SharedQueue::SharedQueue( unsigned long messages, unsigned long maxMessageSize )
		: maxMessageLines( ( maxMessageSize + HSize - 1 ) / LineSize + 1 )
		, totalLines( ( messages + 1 ) * maxMessageLines )			// See note *1 above.
		, pQueue ( new ( align_val_t( LineSize ) ) unsigned long[ totalLines * LineSizeUL ] )
		, pLastSlot( pQueue + ( totalLines - maxMessageLines ) * LineSizeUL )
		, readLines( 0 ) {

	pReadNext = pQueue;
	readStallCount = 0;

	writtenLines = 0;
	freeLines = totalLines;							// In the same line as writtenLines. Keep 1 for sentinel.
	pWriteNext = pQueue;
	writeStallCount = 0;

	writeSentinel();
}


SharedQueue::~SharedQueue() {
	delete [] pQueue;
}


void SharedQueue::writeSentinel() {
	*pWriteNext = 0;			// Set initial sentinel.
}


unsigned char *SharedQueue::getTail() const {
	waitForReader();
	return (unsigned char*)( pWriteNext + 1 );			// We have sufficient space. Current sentinel is here.
}


// We could prime the writer when there is nothing to write and freeLines is low.
void SharedQueue::waitForReader() const {
	unsigned long count = 0;
	while ( freeLines < maxMessageLines * 2 ) {        // 2 because we need that much if we are at the end of the buffer.
		if ( 0 == count ) {
			// Replace with something else later.
			//cout << "Waiting for reader ..." << endl;
			writeStallCount++;
		}
		count++;

		freeLines = totalLines - ( writtenLines - readLines.load( memory_order_relaxed ) );
		//freeLines = totalLines - writtenLines + readLines;
	}
}


void SharedQueue::finishWrite( unsigned long size ) {
	unsigned long* pCurrent = pWriteNext;
	unsigned long messageLines = ( size + HSize - 1 ) / LineSize + 1;
	pWriteNext += messageLines * LineSizeUL;
	unsigned long skippedLines = 0;
	if ( pLastSlot < pWriteNext ) {			// We are too close to the end. Start fresh.
		ptrdiff_t ulsPast = pWriteNext - pLastSlot;
		skippedLines = maxMessageLines - (unsigned long)(ulsPast) / LineSizeUL;	// Lines we are skipping.
		pWriteNext = pQueue;
	}
	writeSentinel();
	auto pHeader = (atomic<unsigned long>*)pCurrent;
	pHeader->store( size, memory_order_release );		// We want everything before this (message data) to be written.
	writtenLines += skippedLines + messageLines;
	freeLines -= skippedLines + messageLines;
}


void SharedQueue::waitForWriter( unsigned long& size ) const {
	unsigned long count = 0;
	auto pHeader = (atomic<unsigned long>*)pReadNext;
	while ( 0 == ( size = pHeader->load( memory_order_acquire ) ) ) {	// We want anything written before this (message data)
		count++;														// to be visible after this.
		if ( 0 == count ) {
			// Replace with something else later.
			// cout << "Waiting for writer ..." << endl;
			readStallCount++;
		}
	}
}


const unsigned char *SharedQueue::getHead( unsigned long& size ) const {
	waitForWriter( size );
	return (const unsigned char*)( pReadNext + 1 );
}


void SharedQueue::finishRead() {
	unsigned long size = *pReadNext;
	unsigned long messageLines = ( size + HSize - 1 ) / LineSize + 1;
	pReadNext += messageLines * LineSizeUL;
	unsigned long skippedLines = 0;
	if ( pLastSlot < pReadNext ) {			// Writer doesn't write too close to the end. Start fresh.
		ptrdiff_t ulsPast = pReadNext - pLastSlot;
		skippedLines = maxMessageLines - (unsigned long)ulsPast / LineSizeUL;	// Lines we are skipping.
		pReadNext = pQueue;
	}
	readLines.store( readLines.load( memory_order_relaxed ) + messageLines + skippedLines, memory_order_relaxed );
	//readLines += messageLines + skippedLines;			// Do we need a guarantee that writer sees this update?
}


ostream& SharedQueue::print( ostream& os ) const {
	os << writeStallCount << ", " << readStallCount;
	return os;
}
