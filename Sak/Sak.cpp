/* Created by Jeevaka Dassanayake on 10/9/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

#include "../Shared/BaseIncludes.hpp"

#include "SakUtils.hpp"

#include "Sak.hpp"
#include "QueueTest/QueueTest.hpp"


int main( int argc, char *argv[] ) {
	return Sak::test( argc, argv );
}


const SakUtils::TestMap Sak::members { { "queue", &QueueTest::test }
/*
	, { "", &::test }
 */
};


int Sak::test( int argc, char **argv ) {
	return SakUtils::invoke( argc, argv, members, 1 );
}
