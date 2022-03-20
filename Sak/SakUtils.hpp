/* Created by Jeevaka Dassanayake on 10/9/17.
   Copyright (c) 2017 Jeevaka Dassanayake.*/

class SakUtils {
public :
	typedef int(*SakTest)(int, char*[], int);
	typedef map<string, SakTest> TestMap;

	static int invoke(int argc, char* argv[], const TestMap& testMap, int index );
	static bool checkArgs( int argc, char* argv[], int index, int expected );

protected :
	// Typedefs


	// Methods


	// Data
};
