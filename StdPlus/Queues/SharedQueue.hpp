/* Created by Jeevaka Dassanayake on 6/24/18.
   Copyright (c) 2018 Jeevaka Dassanayake.*/

namespace StdPlus {

	class SharedQueue {
	public :
		SharedQueue( unsigned long messages, unsigned long maxMessageSize );	// maxMessageSize excl. size (header).
		virtual ~SharedQueue();
		// Writer
		unsigned char* getTail() const;
		void finishWrite( unsigned long size );

		// Reader
		const unsigned char* getHead( unsigned long& size ) const;
		void finishRead();

		ostream& print( ostream& os ) const;

	protected :
		// Typedefs
		static constexpr unsigned LineSize = 64; //hardware_destructive_interference_size;
		static constexpr unsigned long HSize = sizeof( unsigned long );
		static constexpr unsigned LineSizeUL = LineSize / HSize;;

		// Methods
		void waitForReader() const;
		void waitForWriter( unsigned long& size ) const;
		void writeSentinel();

		// Data
		// Shared read only data
		const unsigned long maxMessageLines;		// Maximum number of cache lines used by a single message.
		const unsigned long totalLines;				// Total cache lines in the queue.
		unsigned long* const pQueue;
		unsigned long* const pLastSlot;		// If we start beyond this we cannot give a contiguous block to client.
											// (When writer calls getTail, we only know the size will be smaller than
											// maxMessageLines)
		// Written by Reader, read by writer.
		alignas(LineSize) atomic<unsigned long> readLines;				// Any 64-bit aligned longs are atomic.
		//alignas(LineSize) unsigned long readLines;				// Any 64-bit aligned longs are atomic.
		unsigned long* pReadNext;
		mutable unsigned long readStallCount;

		// Exclusive to writer.
		alignas(LineSize) unsigned long writtenLines;
		mutable unsigned long freeLines;
		unsigned long* pWriteNext;
		mutable unsigned long writeStallCount;
	};
}
