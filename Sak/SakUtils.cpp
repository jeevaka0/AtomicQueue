/* Created by Jeevaka Dassanayake on 10/9/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../Shared/BaseIncludes.hpp"

#include "SakUtils.hpp"


int SakUtils::invoke( int argc, char **argv, const SakUtils::TestMap& testMap, int index ) {
	int result = -1;
	if ( index < argc ) {
		string key( argv[ index++ ] );
		auto it = testMap.find( key );
		if ( testMap.end() != it ) {
			result = ( *it->second )( argc, argv, index );
		} else {
			cerr << "Failed to find an entry for " << key << endl;
		}
	} else {
		cerr << "Too few arguments! (" << argc << ")." << endl;
	}
	return result;
}


bool SakUtils::checkArgs( int argc, char **argv, int index, int expected ) {
	bool success = true;
	if ( argc - index < expected ) {
		for ( int i = 0; i < index ; ++i ) {
			cerr << argv[ i ] << ' ';
		}
		cerr << "expects" << expected << " more arguments" << endl;
		success = false;
	}
	return success;
}
